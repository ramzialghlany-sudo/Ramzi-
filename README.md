# AVR Embedded Project - Temperature Monitoring System

مشروع متكامل لنظام مراقبة درجة الحرارة باستخدام Proteus 8.9 و ATmega328P

## المكونات المتضمنة:
✅ **ADC** - محول التناظري إلى الرقمي (قراءة مستشعر الحرارة)
✅ **LCD** - شاشة عرض 16x2 (عرض درجة الحرارة)
✅ **UART** - اتصال متسلسل مع الكمبيوتر (9600 baud)
✅ **TIMERS** - مؤقتات (Timer0 و Timer1)

## البنية:
```
Ramzi-/
├── src/
│   ├── main.c          # البرنامج الرئيسي
│   ├── config.h        # الإعدادات العامة
│   ├── adc.c           # مكتبة ADC
│   ├── adc.h
│   ├── lcd.c           # مكتبة LCD
│   ├── lcd.h
│   ├── uart.c          # مكتبة UART
│   ├── uart.h
│   ├── timer.c         # مكتبة TIMER
│   └── timer.h
├── Makefile
└── README.md
```

## الميزات الرئيسية:
1. قراءة درجة الحرارة من ADC كل 1 ثانية
2. عرض درجة الحرارة على شاشة LCD
3. إرسال البيانات عبر UART للكمبيوتر
4. استخدام TIMER للعمليات الدورية
5. معالجة الأخطاء والتحقق من الاتصال

## المتحكم المستخدم:
- **ATmega328P** @ 16 MHz

## الإعدادات:
- **ADC**: 10-bit, Single Conversion
- **LCD**: 16x2, 4-bit mode
- **UART**: 9600 baud, 8 bits, 1 stop bit
- **TIMER**: Timer0 (PWM), Timer1 (Compare Mode)

## البدء السريع:
1. افتح Proteus 8.9
2. احمل مشروع المحاكاة
3. اضغط على Run
4. استخدم Serial Monitor لرؤية البيانات
