English | [中文](./README-CN.md)

PHP Tesseract OCR
=======
[![License](https://img.shields.io/badge/license-apache2-blue.svg)](LICENSE)

**PHP Tesseract OCR is a C++ extension of PHP for character recognition and OCR learning in PHP environment.**

## Installation

> This article only introduces the installation of PHP-CPP and PHP Tesseract OCR, Tesseract installation and other configurations. Please go to my personal blog: http://www.5lazy.cn.

### Requirements

- Linux, OS X does not support windows for the time being
- PHP5.6 or later (It is recommended to use php7.0 or more.)
- tesseract 4.0.0 or latest
- PHP-CPP 2.1.2 or the latest (PHP 5.6 uses PHP-CPP-LEGACY)
- GCC 4.8 or later

> ⚠ Before installation, add php-config of the current PHP environment to the environment variable.

### 1. Install PHP-CPP

```shell
//PHP7.0.0 or later
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
//PHP5.6
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

> Because the function of PHPTesseractOCR is not a standard function of PHP, IDE can not be automatically completed. In order to facilitate development, you can click here to download [IDE assistant](http://www.5lazy.cn/), which can be automatically completed under IDE.

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

For other APIs, please consult the manual.

> PHPTesseractOCR Documents Visit [PHPTesseractOCR0.1.1](http://www.5lazy.cn/)

## FAQ

### 1. Is PHPTesseractOCR thread-safe?

Yes. In most cases, it's thread-safe and completely independent unless you use setVariable to change the value of certain parameters.

### 2. Report in PHP cli mode! StrCmp (locale, "C"): Error: Assert failed: in file baseapi. cpp, line 209?

```shell
vim ~/.bash_profile
export LC_ALL=C
source ~/.bash_profile
```

### 3. Report in PHP cli mode! Warning. Invalid resolution 0 dpi. Using 70 instead.

This is a bug in tesserocr. It does not affect the use of tesserocr. Please ignore it.

## License

Apache License Version 2.0 see http://www.apache.org/licenses/LICENSE-2.0.html