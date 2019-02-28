/**
 * Tesseract
 * Author: Albert Zhan <albertzhan666@gmail.com>
 * Copyright (c) 2019-2019 The Albert Zhan
 */

#ifndef TESSERACT_TESSERACT_H
#define TESSERACT_TESSERACT_H

/**
 *  Dependencies
 */
#include <phpcpp.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <map>

using namespace tesseract;
using namespace std;

/**
 *  Class definition
 */
class phpTesseract : public Php::Base
{
private:

    /**
     * The TessBaseAPI from the tesseract library
     */
    tesseract::TessBaseAPI *api;

    /**
     * The Pix from the tesseract library
     */
    Pix *image;

    /**
     * The PageIterator from the tesseract library
     */
    tesseract::PageIterator *it;

    /**
     * Mapping relationship between PHP and tesseract:: OcrEngineMode
     */
    map<string,tesseract::OcrEngineMode> oem;

    /**
     * Mapping relationship between PHP and tesseract::PageSegMode
     */
    map<string,tesseract::PageSegMode> psm;

     /**
     * Mapping relationship between PHP and tesseract::PageIteratorLevel
     */
    map<string,tesseract::PageIteratorLevel> pil;

public:

    /**
	 *  Constructor
	 */
    phpTesseract() = default;

    /**
	 *  Destructor
	 */
    virtual ~phpTesseract() = default;

    /**
	 *  PHP constructor
	 */
    void __construct();

    /**
     * PHP destructor
     */
    void __destruct();

    /**
     *  Setting additional parameters
     *  @param	name	Parameter name
     *  @param	value	parameter values
     *  @return	object	PHP this
     */
    Php::Value setVariable(Php::Parameters &params);

    /**
	 *  Tesseract Initialization
	 *  @param	dir	    Tessdata directory
	 *  @param	lang	Tessdata language pack
	 *  @param	mod	    Engine mode
	 *  @return	object	PHP this
	 */
    Php::Value init(Php::Parameters &params);

    /**
	 *  Setting Paging Mode
     *  @param	name	Paging mode
	 *  @return	object	PHP this
	 */
    Php::Value setPageSegMode(Php::Parameters &params);

    /**
	 *  Setting Recognition Image
	 *  @param	path	Recognized Image Path
	 *  @return	object	PHP this
	 */
    Php::Value setImage(Php::Parameters &params);

    /**
     *  Setting image recognition area
     *  @param	left	Left
     *  @param	top     Top
     *  @param	width   Width
     *  @param	height  Height
     *  @return	object	PHP this
     */
    Php::Value setRectangle(Php::Parameters &params);

    /**
     *  After Recognize, the output is kept internally until the next SetImage
     *  @param	monitor	For the time being, only 0 or null is supported.
     *  @return	object	PHP this
     */
    Php::Value recognize(Php::Parameters &params);

    /**
	 *  Application Paging Layout
	 *  @return	object	PHP this
	 */
    Php::Value analyseLayout();

    /**
     *  Get page layout analysis
     *  @param	orientation	      Page orientation
     *  @param	writingDirection  Writing direction
     *  @param	textlineOrder     Textline order
     *  @param	deskewAngle       Inclination angle
     *  @return	object	PHP this
     */
    Php::Value orientation(Php::Parameters &params);

    /**
     *  Search for text blocks
     *  @param	level	  tesseract::PageIteratorLevel
     *  @param	callable  PHP callback function
     */
    void getComponentImages(Php::Parameters &params);

    /**
	 *  Get result iterator
     *  @param	level	  tesseract::PageIteratorLevel
     *  @param	callable  PHP callback function
	 */
    void getIterator(Php::Parameters &params);

    /**
	 *  Get UTF8 characters
	 *  @return	string
	 */
    Php::Value getUTF8Text();

    /**
     *  Free up recognition results and any stored image data
     */
    void clear();

    /**
	 *  Get php tesseract version
	 *  @return	string
	 */
    Php::Value version();

    /**
	 *  Get tesseract version
	 *  @return	string
	 */
    Php::Value tesseract();

};
#endif
