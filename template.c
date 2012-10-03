/*
    template.c -- JavaScript web page templates
  
    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/********************************* Includes ***********************************/

#include    "goahead.h"
#include    "js.h"

#if BIT_JAVASCRIPT
/********************************** Locals ************************************/

static WebsHash websJsFunctions = -1;  /* Symbol table of functions */

/***************************** Forward Declarations ***************************/

static int  jsRequest(Webs *wp);
static char *strtokcmp(char *s1, char *s2);
static char *skipWhite(char *s);

/************************************* Code ***********************************/
/*
    Process template JS request
 */
static bool jsHandler(Webs *wp)
{
    gassert(websValid(wp));

    if (!smatch(wp->ext, ".asp")) {
        return 0;
    }
    if (jsRequest(wp) < 0) {
        return 1;
    }
    websDone(wp, 200);
    return 1;
}


static void closeJs()
{
    if (websJsFunctions != -1) {
        hashFree(websJsFunctions);
        websJsFunctions = -1;
    }
}


int websJsOpen()
{
    websJsFunctions = hashCreate(WEBS_HASH_INIT * 2);
    websJsDefine("write", websJsWrite);
    websDefineHandler("js", jsHandler, closeJs, 0);
    return 0;
}


/*
    Process requests and expand all scripting commands. We read the entire web page into memory and then process. If
    you have really big documents, it is better to make them plain HTML files rather than Javascript web pages.
 */
static int jsRequest(Webs *wp)
{
    WebsFileInfo    sbuf;
    char            *token, *lang, *result, *ep, *cp, *buf, *nextp, *last;
    ssize           len;
    int             rc, jid;

    gassert(websValid(wp));
    gassert(wp->filename && *wp->filename);

    rc = -1;
    buf = NULL;

    if ((jid = jsOpenEngine(wp->vars, websJsFunctions)) < 0) {
        websError(wp, 200, "Can't create JavaScript engine");
        goto done;
    }
    jsSetUserHandle(jid, wp);

    if (websPageStat(wp, &sbuf) < 0) {
        websError(wp, 404, "Can't stat %s", wp->filename);
        goto done;
    }
    if (websPageOpen(wp, O_RDONLY | O_BINARY, 0666) < 0) {
        websError(wp, 404, "Cannot open URL: %s", wp->filename);
        return 1;
    }
    /*
        Create a buffer to hold the web page in-memory
     */
    len = sbuf.size;
    if ((buf = galloc(len + 1)) == NULL) {
        websError(wp, 200, "Can't get memory");
        goto done;
    }
    buf[len] = '\0';

    if (websPageReadData(wp, buf, len) != len) {
        websError(wp, 200, "Cant read %s", wp->filename);
        goto done;
    }
    websPageClose(wp);
    websWriteHeaders(wp, 200, (ssize) -1, 0);
    websWriteHeader(wp, "Pragma: no-cache\r\nCache-Control: no-cache\r\n");
    websWriteEndHeaders(wp);

    /*
        Scan for the next "<%"
     */
    last = buf;
    rc = 0;
    while (rc == 0 && *last && ((nextp = strstr(last, "<%")) != NULL)) {
        websWriteBlock(wp, last, (nextp - last));
        nextp = skipWhite(nextp + 2);

        /*
            Decode the language
         */
        token = "language";

        if ((lang = strtokcmp(nextp, token)) != NULL) {
            if ((cp = strtokcmp(lang, "=javascript")) != NULL) {
                /* Ignore */;
            } else {
                cp = nextp;
            }
            nextp = cp;
        }

        /*
            Find tailing bracket and then evaluate the script
         */
        if ((ep = strstr(nextp, "%>")) != NULL) {

            *ep = '\0';
            last = ep + 2;
            nextp = skipWhite(nextp);
            /*
                Handle backquoted newlines
             */
            for (cp = nextp; *cp; ) {
                if (*cp == '\\' && (cp[1] == '\r' || cp[1] == '\n')) {
                    *cp++ = ' ';
                    while (*cp == '\r' || *cp == '\n') {
                        *cp++ = ' ';
                    }
                } else {
                    cp++;
                }
            }
            if (*nextp) {
                result = NULL;

                if (jsEval(jid, nextp, &result) == 0) {
                    /*
                         On an error, discard all output accumulated so far and store the error in the result buffer. Be
                         careful if the user has called websError() already.
                     */
                    rc = -1;
                    if (websValid(wp)) {
                        if (result) {
                            websWrite(wp, "<h2><b>Javascript Error: %s</b></h2>\n", result);
                            websWrite(wp, "<pre>%s</pre>", nextp);
                            gfree(result);
                        } else {
                            websWrite(wp, "<h2><b>Javascript Error</b></h2>\n%s\n", nextp);
                        }
                        websWrite(wp, "</body></html>\n");
                        rc = 0;
                    }
                    goto done;
                }
            }

        } else {
            websError(wp, 200, "Unterminated script in %s: \n", wp->filename);
            rc = -1;
            goto done;
        }
    }
    /*
        Output any trailing HTML page text
     */
    if (last && *last && rc == 0) {
        websWriteBlock(wp, last, strlen(last));
    }
    rc = 0;

/*
    Common exit and cleanup
 */
done:
    if (websValid(wp)) {
        websPageClose(wp);
        if (jid >= 0) {
            jsCloseEngine(jid);
        }
    }
    gfree(buf);
    return rc;
}


/*
    Define a Javascript function. Bind an Javascript name to a C procedure.
 */
int websJsDefine(char *name, WebsJsProc fn)
{
    return jsSetGlobalFunctionDirect(websJsFunctions, name, (JsProc) fn);
}


/*
    Javascript write command. This implemements <% write("text"); %> command
 */
int websJsWrite(int jid, Webs *wp, int argc, char **argv)
{
    int     i;

    gassert(websValid(wp));
    
    for (i = 0; i < argc; ) {
        gassert(argv);
        if (websWriteBlock(wp, argv[i], strlen(argv[i])) < 0) {
            return -1;
        }
        if (++i < argc) {
            if (websWriteBlock(wp, " ", 2) < 0) {
                return -1;
            }
        }
    }
    return 0;
}


/*
    Find s2 in s1. We skip leading white space in s1.  Return a pointer to the location in s1 after s2 ends.
 */
static char *strtokcmp(char *s1, char *s2)
{
    ssize     len;

    s1 = skipWhite(s1);
    len = strlen(s2);
    for (len = strlen(s2); len > 0 && (tolower((uchar) *s1) == tolower((uchar) *s2)); len--) {
        if (*s2 == '\0') {
            return s1;
        }
        s1++;
        s2++;
    }
    if (len == 0) {
        return s1;
    }
    return NULL;
}


static char *skipWhite(char *s) 
{
    gassert(s);

    if (s == NULL) {
        return s;
    }
    while (*s && isspace(*s)) {
        s++;
    }
    return s;
}

#endif /* BIT_JAVASCRIPT */

/*
    @copy   default

    Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.

    This software is distributed under commercial and open source licenses.
    You may use the Embedthis GoAhead open source license or you may acquire 
    a commercial license from Embedthis Software. You agree to be fully bound
    by the terms of either license. Consult the LICENSE.md distributed with
    this software for full details and other copyrights.

    Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */
