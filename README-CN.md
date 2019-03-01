中文 | [English](./README.md)

PHP Tesseract OCR
=======
[![License](https://img.shields.io/badge/license-apache2-blue.svg)](LICENSE)

**PHP Tesseract OCR是一个PHP的C++扩展，用于PHP环境下的字符识别和OCR学习。**

## 安装

> 本文只介绍PHP-CPP和PHPTesseractOCR的安装，tesseract的安装以及其他配置请参考本篇文章:http://www.5lazy.cn/post-141.html

### 环境要求

- Linux或OSX暂不支持Windows 
- PHP7.0.0以上
- tesseract4.0.0或最新
- PHP-CPP2.1.2
- GCC4.8或最新

> ⚠ 安装前请把当前PHP环境的php-config添加到环境变量中。

### 1. 安装PHP-CPP

```shell
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
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

## API

### setVariable($name,$value)

设置附加参数

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//例子1
$tesseract->setVariable('save_blob_choices','T');
//例子2
$tesseract->setVariable('tessedit_char_whitelist','0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ');
//例子3
$tesseract->setVariable('tessedit_char_blacklist','xyz');
```

setVariable的参数参考:http://www.sk-spell.sk.cx/tesseract-ocr-parameters-in-302-version


### init($dir,$lang,$mod='OEM_DEFAULT')

初始化Tesseract

traineddata github下载:https://github.com/tesseract-ocr/tessdata  
traineddata百度云下载:https://pan.baidu.com/s/1YVZzGf21b8PQnjPCVP3v9Q 提取码：9n8U 

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//traineddata目录必须以/结尾
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-fast/','eng');
//设置多语言
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-fast/','eng+chi_sim');
//设置识别引擎
$tesseract->setVariable('save_blob_choices','T')->init(__DIR__.'/traineddata/tessdata-raw/','eng','OEM_TESSERACT_LSTM_COMBINED');
```

Engine Mode Options:
- OEM_DEFAULT(Default, based on what is available.)
- OEM_LSTM_ONLY(Neural nets LSTM engine only.)
- OEM_TESSERACT_LSTM_COMBINED(Legacy + LSTM engines.)
- OEM_TESSERACT_ONLY(Legacy engine only.)

### setPageSegMode($name)

设置页面分割模式

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO');
```
页面分割参数参考:https://rmtheis.github.io/tess-two/javadoc/com/googlecode/tesseract/android/TessBaseAPI.PageSegMode.html
### setImage($path)

设置需要识别的图片

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
//支持png, jpg, jpeg, tif, webp格式
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png');
```

### setRectangle($left,$top,$width,$height)

设置图像识别区域

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

识别后，输出在内部保存，直到下一个setimage

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->setVariable('save_blob_choices','T')
->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setPageSegMode('PSM_AUTO')
->setImage(__DIR__.'/img/1.png')
->setRectangle(100,100,100,100)
//目前参数仅支持0或null。
->recognize(0);
```

### analyseLayout()

应用页面分割布局分析

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

获取页面布局分析

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

搜索文字图块

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

获取结果迭代器

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
有关参数，请参阅getComponentImages

### getUTF8Text()

获取识别后的UTF8文本

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$text=$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
->setImage(__DIR__.'/img/1.png')
->getUTF8Text();
echo $text;
```

### clear()

释放识别结果和任何存储的图像数据

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
$tesseract->init(__DIR__.'/traineddata/tessdata-fast/','eng')
//三幅图像被正常识别。
for($i=1;$i<=3;$i++){
    $tesseract->setImage(__DIR__.'/img/'.$i.'.png')
    echo $tesseract->getUTF8Text();
}
//只能被识别一张，后两张被释放了
for($i=1;$i<=3;$i++){
   $tesseract->setImage(__DIR__.'/img/'.$i.'.png')
   echo $tesseract->getUTF8Text();
   $tesseract->clear();
}
```

### version()

获取PHP Tesseract OCR版本号

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
echo $tesseract->version();
```

### tesseract()

获取tesseract版本号

```php
use tesseract_ocr\Tesseract;
$tesseract=new Tesseract();
echo $tesseract->tesseract();
```

## 问题交流

QQ交流群：24379498

## License

Apache License Version 2.0 see http://www.apache.org/licenses/LICENSE-2.0.html
