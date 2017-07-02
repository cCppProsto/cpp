#include <iostream>
#include <string>

using namespace std;

#include "glmain.h"
#include <glut.h>

/*
struct Document
{
    void open(string aFileName)
    {
        mFileName = aFileName;
    }
    void read()
    {
    }
    void close()
    {
    }

    const string &text() const
    {
        return mText;
    }

    const string &fileName() const
    {
        return mFileName;
    }

protected:
    string mText;
    // FILE*
private:
    string mFileName;
};

struct epubDoc : Document
{
    void read()
    {
        mText = fileName();
    }
};

struct pdfDoc : Document
{
    void read()
    {
        mText = fileName();
    }
};

Document doc;
epubDoc epub;
pdfDoc  pdf;

// if EPUB
epub.open("Epub");
epub.read();
std::cout << epub.text() << std::endl;

// IF PDF
pdf.open("PDF");
pdf.read();
std::cout << pdf.text() << std::endl;
*/

/*
struct IDocument
{
    void open(string aFileName){mFileName = aFileName;}
    void close(){}

    virtual void read() = 0;

    const string &text() const { return mText;}
    const string &fileName() const { return mFileName;}

protected:
    string mText;
private:
    string mFileName;
};

struct epubDoc : IDocument
{
    void read()
    {
        mText = fileName();
    }
};

struct pdfDoc : IDocument
{
    void read()
    {
        mText = fileName();
    }
};

struct rtfDoc : IDocument
{
    void read()
    {
        mText = fileName();
    }
};

void print_doc_text(IDocument *pDoc, string aName)
{
    if(pDoc != nullptr)
    {
        pDoc->open(aName);
        pDoc->read();
        std::cout << pDoc->text() << std::endl;
    }
}

struct A
{
    virtual void a(){}
    virtual void b(){}
};

tbvf - A
[addr(0x0000) - A::a]


struct B : A
{
    void a(){}
};


IDocument *pDoc = nullptr;

// if EPUB
pDoc = new epubDoc;
print_doc_text(pDoc, "Epub");

//if PDF
pDoc = new pdfDoc;
print_doc_text(pDoc, "pdf");

//if RTF
pDoc = new rtfDoc;
print_doc_text(pDoc, "rtf");


return 0 ;

tbvf - B
[addr(0x00FF) - A::a]

A *pobj = 0;

pobj = new B;

tbvf[0x00FF]

pobj->a()
*/

int main(int argcp, char **argv)
{
    glutInit(&argcp, argv);

    glMain glw;
    glw.run();
    return 0;

    return 0;
}
