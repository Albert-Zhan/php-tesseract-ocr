English | [中文](./README-CN.md)

PHP Tesseract OCR
=======
[![License](https://img.shields.io/badge/license-apache2-blue.svg)](LICENSE)

**PHP Tesseract OCR is a C++ extension of PHP for character recognition and OCR learning in PHP environment.**

## Installation

> This article only introduces the installation of PHP-CPP and PHP TesseractOCR. For Tesseract installation and other configuration, please refer to this article: http://www.5lazy.cn.

### Requirements

- Linux, OS X does not support windows for the time being
- PHP5.6 or later (It is recommended to use php7.0 or more.)
- tesseract 4.0.0 or latest
- PHP-CPP 2.1.2 or the latest (PHP 5.6 uses PHP-CPP-LEGACY)
- GCC 4.8 or later

> ⚠ Before installation, add php-config of the current PHP environment to the environment variable.

### 1. Install PHP-CPP

```shell
#PHP7.0.0 or later
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
#PHP5.6
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP-LEGACY.git
cd PHP-CPP-LEGACY
make
sudo make install
```
If there are multiple warnings in OSX compilation, please ignore them

> ⚠ To do this, make sure that Tesseract version 4.0.0 or above is installed.

### 2. Install PHP Tesseract OCR

```shell
git clone https://github.com/2654709623/php-tesseract-ocr.git
cd php-tesseract-ocr
make
sudo make install
```

If there are multiple warnings in OSX compilation, please ignore them

## Example

> Because the function of PHPTesseractOCR is not a standard function of PHP, IDE can not be automatically completed. In order to facilitate development, you can click here to download [IDE assistant](http://47.93.187.229/helper.zip), which can be automatically completed under IDE.

### 1. Simple Character Recognition

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->getUTF8Text();
echo $text;
```

### 2. Search for text blocks

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png');
$tesseract->getComponentImages('RIL_WORD',function ($x,$y,$w,$h,$text){
    echo "Result:{$text}X:{$x}Y:{$y}Width:{$w}Height:{$h}";
    echo '<br>';
});
```

### 3. Get result iterator

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')->recognize(0);
$tesseract->getIterator('RIL_TEXTLINE',function ($text,$x1,$y1,$x2,$y2){
    echo "Text:{$text}X1:{$x1}Y1:{$y1}X2:{$x2}Y2:{$y2}";
    echo '<br>';
});
echo $tesseract->getUTF8Text();
```

### 4. Setting image recognition area

Help to improve recognition speed
```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
->getUTF8Text();
echo $text;
```

### 5. Setting Page Segmentation Mode

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->recognize(0)
->analyseLayout()
echo $tesseract->getUTF8Text();
```

## API

### setVariable($name,$value)

Setting additional parameters

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//Example1
$tesseract->setVariable('save_blob_choices','T');
//Example2
$tesseract->setVariable('tessedit_char_whitelist','0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ');
//Example3
$tesseract->setVariable('tessedit_char_blacklist','xyz');
```

setVariable Options Reference:http://www.sk-spell.sk.cx/tesseract-ocr-parameters-in-302-version


### init($dir,$lang,$mod='OEM_DEFAULT')

Tesseract initialization

Traineddata download:https://github.com/tesseract-ocr/tessdata

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//Traineddata directory must / end
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-fast/','eng');
//Multiple languages
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-fast/','eng+chi_sim');
//Setting Engine Mode
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-raw/','eng','OEM_TESSERACT_LSTM_COMBINED');
```

Engine Mode Options:
- OEM_DEFAULT(Default, based on what is available.)
- OEM_LSTM_ONLY(Neural nets LSTM engine only.)
- OEM_TESSERACT_LSTM_COMBINED(Legacy + LSTM engines.)
- OEM_TESSERACT_ONLY(Legacy engine only.)

### setPageSegMode($name)

Setting Paging Mode

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO');
```
PageSegMode Options Reference:https://rmtheis.github.io/tess-two/javadoc/com/googlecode/tesseract/android/TessBaseAPI.PageSegMode.html
### setImage($path)

Setting Recognition Pictures

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//Support png, jpg, jpeg, tif, webp format
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png');
```

### setRectangle($left,$top,$width,$height)

Setting image recognition area

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100);
```

### recognize($monitor)

After Recognize, the output is kept internally until the next SetImage

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
//For the time being, only 0 or null is supported.
->recognize(0);
```

### analyseLayout()

Application Paging Layout

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
->recognize(0)
->analyseLayout();
```

### orientation(&$orientation,&$writingDirection,&$textlineOrder,&$deskewAngle)

Get page layout analysis

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
->recognize(0)
->analyseLayout()
->orientation($orientation,$writingDirection,$textlineOrder,$deskewAngle);
```

### getComponentImages($level,$callable)

Search for text blocks

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png');
$tesseract->getComponentImages('RIL_WORD',function ($x,$y,$w,$h,$text){
    echo "Result:{$text}X:{$x}Y:{$y}Width:{$w}Height:{$h}";
    echo '<br>';
});
```

PageIteratorLevel Options:
- RIL_BLOCK(Block of text/image/separator line.)
- RIL_PARA(Paragraph within a block.)
- RIL_TEXTLINE(Line within a paragraph.)
- RIL_WORD(Word within a textline.)
- RIL_SYMBOL(Symbol/character within a word.)

### getIterator($level,$callable)

Get result iterator

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')->recognize(0);
$tesseract->getIterator('RIL_TEXTLINE',function ($text,$x1,$y1,$x2,$y2){
    echo "Text:{$text}X1:{$x1}Y1:{$y1}X2:{$x2}Y2:{$y2}";
    echo '<br>';
});
```
See getComponentImages for parameters

### getUTF8Text()

Get UTF8 characters

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->getUTF8Text();
echo $text;
```

### clear()

Free up recognition results and any stored image data

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
//Three images were recognized normally.
for($i=1;$i<=3;$i++){
    $tesseract->setImage(__DIR__.'/img/'.$i.'.png')
    echo $tesseract->getUTF8Text();
}
//Only one can be identified.
for($i=1;$i<=3;$i++){
   $tesseract->setImage(__DIR__.'/img/'.$i.'.png')
   echo $tesseract->getUTF8Text();
   $tesseract->clear();
}
```

### version()

Get php tesseract version

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
echo $tesseract->version();
```

### tesseract()

Get tesseract version

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
echo $tesseract->tesseract();
```

## Issue

QQ Group：24379498

## License

Apache License Version 2.0 see http://www.apache.org/licenses/LICENSE-2.0.html
