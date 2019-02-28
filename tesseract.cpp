/**
 * Tesseract
 * Author: Albert Zhan <albertzhan666@gmail.com>
 * Copyright (c) 2019-2019 The Albert Zhan
 */

/**
*  Dependencies
*/
#include "tesseract.h"

/**
 *  PHP constructor
 */
void phpTesseract::__construct()
{
    this->api = new tesseract::TessBaseAPI();

    //Mapping relationship between PHP and tesseract:: OcrEngineMode
    this->oem["OEM_TESSERACT_ONLY"] = tesseract::OEM_TESSERACT_ONLY;
    this->oem["OEM_TESSERACT_LSTM_COMBINED"] = tesseract::OEM_TESSERACT_LSTM_COMBINED;
    this->oem["OEM_LSTM_ONLY"] = tesseract::OEM_LSTM_ONLY;
    this->oem["OEM_DEFAULT"] = tesseract::OEM_DEFAULT;

    //Mapping relationship between PHP and tesseract::PageSegMode
    this->psm["PSM_OSD_ONLY"] = tesseract::PSM_OSD_ONLY;
    this->psm["PSM_AUTO_OSD"] = tesseract::PSM_AUTO_OSD;
    this->psm["PSM_AUTO_ONLY"] = tesseract::PSM_AUTO_ONLY;
    this->psm["PSM_AUTO"] = tesseract::PSM_AUTO;
    this->psm["PSM_SINGLE_COLUMN"] = tesseract::PSM_SINGLE_COLUMN;
    this->psm["PSM_SINGLE_BLOCK_VERT_TEXT"] = tesseract::PSM_SINGLE_BLOCK_VERT_TEXT;
    this->psm["PSM_SINGLE_BLOCK"] = tesseract::PSM_SINGLE_BLOCK;
    this->psm["PSM_SINGLE_LINE"] = tesseract::PSM_SINGLE_LINE;
    this->psm["PSM_SINGLE_WORD"] = tesseract::PSM_SINGLE_WORD;
    this->psm["PSM_CIRCLE_WORD"] = tesseract::PSM_CIRCLE_WORD;
    this->psm["PSM_SINGLE_CHAR"] = tesseract::PSM_SINGLE_CHAR;
    this->psm["PSM_SPARSE_TEXT"] = tesseract::PSM_SPARSE_TEXT;
    this->psm["PSM_SPARSE_TEXT_OSD"] = tesseract::PSM_SPARSE_TEXT_OSD;
    this->psm["PSM_RAW_LINE"] = tesseract::PSM_RAW_LINE;
    this->psm["PSM_COUNT"] = tesseract::PSM_COUNT;

    //Mapping relationship between PHP and tesseract::PageIteratorLevel
    this->pil["RIL_BLOCK"] = tesseract::RIL_BLOCK;
    this->pil["RIL_PARA"] = tesseract::RIL_PARA;
    this->pil["RIL_TEXTLINE"] = tesseract::RIL_TEXTLINE;
    this->pil["RIL_WORD"] = tesseract::RIL_WORD;
    this->pil["RIL_SYMBOL"] = tesseract::RIL_SYMBOL;
}

/**
 * PHP destructor
 */
void phpTesseract::__destruct()
{
    this->api->End();
    pixDestroy(&this->image);
}

/**
 *  Setting additional parameters
 *  @param	name	Parameter name
 *  @param	value	parameter values
 *  @return	object	PHP this
 */
Php::Value phpTesseract::setVariable(Php::Parameters &params)
{
    try
    {
        this->api->SetVariable(params[0],params[1]);
    }
    catch (...)
    {
        Php::error << "Error setting variable function" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Tesseract Initialization
 *  @param	dir	    Tessdata directory
 *  @param	lang	Tessdata language pack
 *  @param	mod	    Engine mode
 *  @return	object	PHP this
 */
Php::Value phpTesseract::init(Php::Parameters &params)
{
    try
    {
        if (params.size() == 2)
        {
            this->api->Init(params[0], params[1]);
        }
        else
        {
            this->api->Init(params[0], params[1], this->oem[params[2]]);
        }
    }
    catch (...)
    {
        Php::error << "Initialization function setting error" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Setting Paging Mode
 *  @param	name	Paging mode
 *  @return	object	PHP this
 */
Php::Value phpTesseract::setPageSegMode(Php::Parameters &params)
{
    try
    {
        this->api->SetPageSegMode(psm[params[0]]);
    }
    catch (...)
    {
        Php::error << "Error setting paging mode function" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Setting Recognition Image
 *  @param	path	Recognized Image Path
 *  @return	object	PHP this
 */
Php::Value phpTesseract::setImage(Php::Parameters &params)
{
    try
    {
        this->image = pixRead(params[0]);
        this->api->SetImage(image);
    }
    catch (...)
    {
        Php::error << "Error setting picture function" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Setting image recognition area
 *  @param	left	Left
 *  @param	top     Top
 *  @param	width   Width
 *  @param	height  Height
 *  @return	object	PHP this
 */
Php::Value phpTesseract::setRectangle(Php::Parameters &params)
{
    try
    {
        this->api->SetRectangle(params[0],params[1],params[2],params[3]);
    }
    catch (...)
    {
        Php::error << "Error setting image subrectangle" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  After Recognize, the output is kept internally until the next SetImage
 *  @param	monitor	For the time being, only 0 or null is supported.
 *  @return	object	PHP this
 */
Php::Value phpTesseract::recognize(Php::Parameters &params)
{
    try
    {
        //TODO ETEXT_DESC class is not supported for the time being
        if(params[0]==0)
        {
            this->api->Recognize(0);
        }
        else
        {
            this->api->Recognize(NULL);
        }
    }
    catch (...)
    {
        Php::error << "Error using Recognize function" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Application Paging Layout
 *  @return	object	PHP this
 */
Php::Value phpTesseract::analyseLayout()
{
    try
    {
        this->it=this->api->AnalyseLayout();
    }
    catch (...)
    {
        Php::error << "Analysis Layout function call error" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Get page layout analysis
 *  @param	orientation	      Page orientation
 *  @param	writingDirection  Writing direction
 *  @param	textlineOrder     Textline order
 *  @param	deskewAngle       Inclination angle
 *  @return	object	PHP this
 */
Php::Value phpTesseract::orientation(Php::Parameters &params)
{
    tesseract::Orientation orientation;
    tesseract::WritingDirection direction;
    tesseract::TextlineOrder order;
    float deskew_angle;
    try
    {
        this->it->Orientation(&orientation,&direction,&order,&deskew_angle);
        params[0]=orientation;
        params[1]=direction;
        params[2]=order;
        params[3]=deskew_angle;
    }
    catch (...)
    {
        Php::error << "Error getting page layout analysis" << std::flush;
    }
    Php::Value self(this);
    return self;
}

/**
 *  Search for text blocks
 *  @param	level	  tesseract::PageIteratorLevel
 *  @param	callable  PHP callback function
 */
void phpTesseract::getComponentImages(Php::Parameters &params)
{
    try
    {
        Boxa *boxes=api->GetComponentImages(this->pil[params[0]],true,NULL,NULL);
        Php::Value callback=params[1];
        for (int i=0;i<boxes->n;i++)
        {
            BOX *box = boxaGetBox(boxes,i,L_CLONE);
            api->SetRectangle(box->x,box->y,box->w,box->h);
            char *ocrResult = api->GetUTF8Text();
            callback(box->x,box->y,box->w,box->h,ocrResult);
            delete ocrResult;
        }
    }
    catch (...)
    {
        Php::error << "Error executing getComponentImages" << std::flush;
    }
}

/**
 *  Get result iterator
 *  @param	level	  tesseract::PageIteratorLevel
 *  @param	callable  PHP callback function
 */
void phpTesseract::getIterator(Php::Parameters &params)
{
      try
      {
           tesseract::ResultIterator *ri =this->api->GetIterator();
           int x1, y1, x2, y2;
           Php::Value callback=params[1];
           do
           {
               const char *word = ri->GetUTF8Text(this->pil[params[0]]);
               ri->BoundingBox(this->pil[params[0]],&x1, &y1, &x2, &y2);
               callback(word,x1,y1,x2,y2);
               delete[] word;
           } while(ri->Next(this->pil[params[0]]));
      }
      catch (...)
      {
          Php::error << "Error executing getIterator" << std::flush;
      }
}

/**
 *  Get UTF8 characters
 *  @return	string
 */
Php::Value phpTesseract::getUTF8Text()
{
    return this->api->GetUTF8Text();
}

/**
 *  Free up recognition results and any stored image data
 */
void phpTesseract::clear()
{
    try
    {
       this->api->Clear();
    }
    catch (...)
    {
        Php::error << "Error clearing data" << std::flush;
    }
}

/**
 *  Get php tesseract version
 *  @return	string
 */
Php::Value phpTesseract::version()
{
    return "0.1.1";
}

/**
 *  Get tesseract version
 *  @return	string
 */
Php::Value phpTesseract::tesseract()
{
    return this->api->Version();
}
