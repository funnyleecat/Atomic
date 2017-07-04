#ifndef __CC_PRINT_HPP__
#define __CC_PRINT_HPP__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <iostream>
#include <exception>

#ifdef WIN32
#pragma warning(disable:4996)
#endif

namespace CC
{
    class Print
    {
        Print(){ }
        Print(const Print&);
        Print & operator = (const Print&);
    public:
        enum CHOSE{ TO_ALL, TO_CMD, TO_FILE };
        static void ToTerminal(bool bVal, bool bNewLine = true)
        {
            std::cout << (bVal ? "true" : "false");
            TerminalNewline(bNewLine);
            return;
        }
        static void ToTerminal(int nVal, bool bNewLine = true)
        {
            std::cout << nVal;
            TerminalNewline(bNewLine);
            return;
        }
        static void ToTerminal(double dVal, bool bNewLine = true)
        {
            std::cout << dVal;
            TerminalNewline(bNewLine);
            return;
        }
        static void ToTerminal(bool bNewLine, unsigned int nBufLen, const char* pStr, ...)
        {
            char* buf = new(std::nothrow) char[nBufLen + 1];
            if (NULL == buf)
            {
                TerminalNewline(bNewLine);
                return;
            }
            memset(buf, 0, nBufLen + 1);
            va_list argptr;
            va_start(argptr, pStr);
            int nRet = vsnprintf(buf, nBufLen, pStr, argptr);
            nRet =0;
            va_end(argptr);
            std::cout << buf;
            TerminalNewline(bNewLine);
            delete[] buf;
            buf = NULL;
            return;
        }
        static void ToTerminal(const char* pStr, bool bNewLine = true)
        {
            std::cout << pStr;
            TerminalNewline(bNewLine);
            return;
        }
        static void ToTerminal(const std::string& str, bool bNewLine = true)
        {
            std::cout << str;
            TerminalNewline(bNewLine);
            return;
        }
        static void ToTerminal(const std::exception& e, bool bNewLine = true)
        {
            Print::ToTerminal(bNewLine, (unsigned int)strlen(e.what()), e.what());
        }
        static bool ToFile(const std::string& filePath, bool bVal, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fputs((bVal ? "true" : "false"), pFILE);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        static bool ToFile(const std::string& filePath, int nVal, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fprintf(pFILE, "%d", nVal);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        static bool ToFile(const std::string& filePath, double dVal, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fprintf(pFILE, "%f", dVal);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        static bool ToFile(const std::string& filePath, const char* pStr, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fputs(pStr, pFILE);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        static bool ToFile(const std::string& filePath, bool bNewLine, bool bAppend, unsigned int nBufLen, const char* pStr, ...)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (!pFILE)
            {
                return false;
            }
            do
            {
                char* buf = new(std::nothrow) char[nBufLen + 1];
                if (NULL == buf)
                {
                    break;
                }
                memset(buf, 0, nBufLen + 1);
                va_list argptr;
                va_start(argptr, pStr);
                int nRet = vsnprintf(buf, nBufLen, pStr, argptr);
                nRet=0;
                va_end(argptr);
                fputs(buf, pFILE);
                delete[] buf;
                buf = NULL;
            } while (0);
            TerminalNewline(bNewLine, pFILE);
            fclose(pFILE);
            return true;
        }
        static bool ToFile(const std::string& filePath, const std::string& strContent, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fputs(strContent.c_str(), pFILE);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        static bool ToFile(const std::string& filePath, const std::exception& e, bool bNewLine = true, bool bAppend = true)
        {
            FILE* pFILE = FileOpen(filePath, bAppend);
            if (pFILE)
            {
                fputs(e.what(), pFILE);
                TerminalNewline(bNewLine, pFILE);
                fclose(pFILE);
                return true;
            }
            return false;
        }
        //static bool operator ()(CHOSE eCHOSE)
        //{
        // }
    private:
        static void TerminalNewline(bool bNewLine)
        {
            if (bNewLine)
            {
                std::cout << std::endl;
            }
        }
        static void TerminalNewline(bool bNewLine, FILE* pFILE)
        {
            if (bNewLine)
            {
                fputs("\n", pFILE);
            }
            return;
        }
        static FILE* FileOpen(const std::string& strFilePath, bool bAppend)
        {
            return fopen(strFilePath.c_str(), (bAppend ? "a+" : "w+"));
        }
    };
}

#endif //__CC_PRINT_HPP__
