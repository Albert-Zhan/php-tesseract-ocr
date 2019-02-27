中文 | [English](./README.md)

PHP Tesseract OCR
=======
[![License](https://img.shields.io/badge/license-apache2-blue.svg)](LICENSE)

**PHP Tesseract OCR是一个PHP的C++扩展，用于PHP环境下的字符识别和OCR学习。**

## 安装

> 本文只介绍PHP-CPP和PHPTesseractOCR的安装，tesseract的安装以及其他配置请移步到我的个人博客:http://www.5lazy.cn。

### 环境要求

- Linux或OSX暂不支持Windows 
- PHP5.6或最新(建议使用PHP7.0.0以上)
- tesseract4.0.0或最新
- PHP-CPP2.1.2或最新(PHP7以下PHP5以上使用PHP-CPP-LEGACY)
- GCC4.8或最新

> ⚠ 安装前请把当前PHP环境的php-config添加到环境变量中。

### 1. 安装PHP-CPP

```shell
#PHP7.0.0以上
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
#PHP7以下PHP5以上
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP-LEGACY.git
cd PHP-CPP-LEGACY
make
sudo make install
```
OSX在编译中如果出现多处警告请忽略

> ⚠ 到这一步请确定已经安装好tesseract4.0.0以上版本。

### 2. 安装PHPTesseractOCR

```shell
git clone https://github.com/2654709623/php-tesseract-ocr.git
cd php-tesseract-ocr
make
sudo make install
```

OSX在编译中如果出现多处警告请忽略

## 例子

> 由于PHPTesseractOCR的函数并不是PHP标准函数，IDE无法进行自动补全，为了方便开发可以点此下载[IDE助手](http://47.93.187.229/helper.zip)，在IDE下即可自动补全 。

### 1. 简单的字符识别

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->getUTF8Text();
echo $text;
```

### 2. 搜索文字图块

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

### 3. 获取结果迭代器

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

### 4. 设置图像识别区域

有助于提高识别速度
```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
->getUTF8Text();
echo $text;
```

### 5. 设置页面分割模式

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

其他API请查看手册

> PHPTesseractOCR使用文档请访问 [PHPTesseractOCR0.1.1](http://www.5lazy.cn/)

## 常见问题

### 1. PHPTesseractOCR是否是线程安全?

是。大多数情况下是线程安全的，并且是完全独立的，除非你使用了setVariable改变了某些参数的值。

### 2. PHPCli模式下!StrCmp (locale, "C"): Error: Assert failed: in file baseapi. cpp, line 209?

```shell
vim ~/.bash_profile
export LC_ALL=C
source ~/.bash_profile
```

### 3. PHPCli模式下Warning. Invalid resolution 0 dpi. Using 70 instead.

此情况是tesserocr的bug，不影响使用，请忽略。

## License

Apache License Version 2.0 see http://www.apache.org/licenses/LICENSE-2.0.html