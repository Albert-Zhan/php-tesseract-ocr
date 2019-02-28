/**
 * Tesseract
 * Author: Albert Zhan <albertzhan666@gmail.com>
 * Copyright (c) 2019-2019 The Albert Zhan
 */

 /**
 *  Dependencies
 */
#include "tesseract.h"

// Symbols are exported according to the "C" language
extern "C" {
// export the "get_module" function that will be called by the Zend engine
PHPCPP_EXPORT void *get_module()
{
    // create extension
    static Php::Extension extension("tesseract", "0.1.1");

    // create a namespace
    Php::Namespace tesseract_ocr("tesseract_ocr");

    // the Tesseract class
    Php::Class<phpTesseract> phpTesseractClass("Tesseract");
    phpTesseractClass.method<&phpTesseract::__construct>("__construct");
    phpTesseractClass.method<&phpTesseract::__destruct>("__destruct");
    phpTesseractClass.method<&phpTesseract::setVariable>("setVariable", {
            Php::ByVal("name",Php::Type::String),
            Php::ByVal("value",Php::Type::String)
    });
    phpTesseractClass.method<&phpTesseract::init>("init", {
            Php::ByVal("dir",Php::Type::String),
            Php::ByVal("lang",Php::Type::String),
            Php::ByVal("mod",Php::Type::String,false)
    });
    phpTesseractClass.method<&phpTesseract::setPageSegMode>("setPageSegMode", {
            Php::ByVal("name",Php::Type::String)
    });
    phpTesseractClass.method<&phpTesseract::setImage>("setImage", {
            Php::ByVal("path",Php::Type::String)
    });
    phpTesseractClass.method<&phpTesseract::setRectangle>("setRectangle", {
            Php::ByVal("left",Php::Type::Numeric),
            Php::ByVal("top",Php::Type::Numeric),
            Php::ByVal("width",Php::Type::Numeric),
            Php::ByVal("height",Php::Type::Numeric)
    });
    phpTesseractClass.method<&phpTesseract::recognize>("recognize",{
            Php::ByVal("monitor")
    });
    phpTesseractClass.method<&phpTesseract::analyseLayout>("analyseLayout");
    phpTesseractClass.method<&phpTesseract::orientation>("orientation",{
            Php::ByRef("orientation"),
            Php::ByRef("writingDirection"),
            Php::ByRef("textlineOrder"),
            Php::ByRef("deskewAngle")
    });
    phpTesseractClass.method<&phpTesseract::getComponentImages>("getComponentImages",{
            Php::ByVal("level",Php::Type::String),
            Php::ByVal("callable")
    });
    phpTesseractClass.method<&phpTesseract::getIterator>("getIterator",{
             Php::ByVal("level",Php::Type::String),
             Php::ByVal("callable")
    });
    phpTesseractClass.method<&phpTesseract::getUTF8Text>("getUTF8Text");
    phpTesseractClass.method<&phpTesseract::clear>("clear");
    phpTesseractClass.method<&phpTesseract::version>("version");
    phpTesseractClass.method<&phpTesseract::tesseract>("tesseract");

    // add all classes to the namespace
    tesseract_ocr.add(std::move(phpTesseractClass));

    // add the namespace to the extension
    extension.add(std::move(tesseract_ocr));

    // return the extension module
    return extension;
}
}
