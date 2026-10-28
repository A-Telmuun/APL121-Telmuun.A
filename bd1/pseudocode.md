# Псевдокод — Сэдэв №29: Хуанли хэвлэгч

Блок схем (`quest.fprg`)-ийн функц бүр доор ижил нэрээр, ижил дарааллаар бичигдсэн.
`main.c` дахь C функцүүд мөн адил нэртэй (жишээ нь `IsLeap` → `is_leap`).

Гарагийн дугаар: **0 = Даваа, 1 = Мягмар, … , 6 = Ням**.

---

## Function IsLeap(y) → Boolean
```
leap ← (y % 4 == 0 AND y % 100 != 0) OR y % 400 == 0
RETURN leap
```

## Function DaysInMonth(y, m) → Integer   *(else-if шат)*
```
IF m == 2 THEN
    IF IsLeap(y) THEN days ← 29 ELSE days ← 28
ELSE IF m == 4 OR m == 6 OR m == 9 OR m == 11 THEN
    days ← 30
ELSE
    days ← 31
RETURN days
```

## Function DayNumber(y, m, d) → Integer
1900-01-01 (Даваа)-ээс хойш өнгөрсөн хоногийн тоо.
```
total ← 0
FOR yy ← 1900 TO y − 1
    IF IsLeap(yy) THEN total ← total + 366 ELSE total ← total + 365
FOR mm ← 1 TO m − 1
    total ← total + DaysInMonth(y, mm)
total ← total + d − 1
RETURN total
```
Тухайн өдрийн гараг = `DayNumber(y, m, d) % 7`.

## Function WeekdayName(w) → String   *(else-if шат)*
```
IF w == 0 THEN wdName ← "Даваа"
ELSE IF w == 1 THEN wdName ← "Мягмар"
ELSE IF w == 2 THEN wdName ← "Лхагва"
ELSE IF w == 3 THEN wdName ← "Пүрэв"
ELSE IF w == 4 THEN wdName ← "Баасан"
ELSE IF w == 5 THEN wdName ← "Бямба"
ELSE wdName ← "Ням"
RETURN wdName
```

## Function IsHoliday(m, d) → Boolean
```
hol ← (m==1 AND d==1) OR (m==3 AND d==8) OR (m==6 AND d==1)
      OR (m==7 AND d>=11 AND d<=15) OR (m==11 AND d==26) OR (m==12 AND d==29)
RETURN hol
```

## Function ReadYear() → Integer   *(do-while оролтын шалгалт)*
```
DO
    OUTPUT "Он оруулна уу (1900-2100): "
    INPUT y
    IF y < 1900 OR y > 2100 THEN OUTPUT "Алдаа: он 1900-2100 хооронд байх ёстой!"
WHILE y < 1900 OR y > 2100
RETURN y
```

## Function ReadMonth() → Integer
```
DO
    OUTPUT "Сар оруулна уу (1-12): "
    INPUT m
    IF m < 1 OR m > 12 THEN OUTPUT "Алдаа: сар 1-12 хооронд байх ёстой!"
WHILE m < 1 OR m > 12
RETURN m
```

## Function ReadDay(y, m) → Integer
```
maxDay ← DaysInMonth(y, m)
DO
    OUTPUT "Өдөр оруулна уу (1-" & maxDay & "): "
    INPUT d
    IF d < 1 OR d > maxDay THEN OUTPUT "Алдаа: өдөр 1-" & maxDay & " хооронд байх ёстой!"
WHILE d < 1 OR d > maxDay
RETURN d
```

## Procedure PrintCalendar(y, m)   *(Main-аас **Call** блокоор дуудна)*
```
days     ← DaysInMonth(y, m)
startCol ← DayNumber(y, m, 1) % 7          // 1-ний өдөр аль баганаас эхлэх
OUTPUT "      " & y & " оны " & m & "-р сар"
OUTPUT " Да  Мя  Лх  Пү  Ба  Бя  Ня"
FOR column ← 0 TO startCol − 1
    OUTPUT "    " (мөр шилжихгүй)          // хоосон нүд
column ← startCol
FOR dayNo ← 1 TO days
    OUTPUT dayNo-г 3 тэмдэгтийн өргөнтэй (мөр шилжихгүй)
    IF IsHoliday(m, dayNo) THEN OUTPUT "*" ELSE OUTPUT " "
    column ← column + 1
    IF column == 7 THEN                     // Ням гарагийн дараа шинэ мөр
        OUTPUT шинэ мөр
        column ← 0
IF column != 0 THEN OUTPUT шинэ мөр
OUTPUT "(* = нийтээр амрах баярын өдөр)"
```

---

## Main
```
OUTPUT "=== ХУАНЛИ ХЭВЛЭГЧ (Сэдэв №29) ==="

// 1. Оролт
year  ← ReadYear()
month ← ReadMonth()

// 2. Өндөр жил ба сарын хоног
IF IsLeap(year) THEN OUTPUT year & " он: өндөр жил (366 хоног)"
ELSE                 OUTPUT year & " он: энгийн жил (365 хоног)"
OUTPUT month & "-р сар " & DaysInMonth(year, month) & " хоногтой"

// 3. Сарын хуанли
CALL PrintCalendar(year, month)

// 4. Жилийн тойм хүснэгт (12 мөр) + "Баасан 13"-ыг хайх
OUTPUT " Сар  Хоног  Баяр   Эхлэх гараг"
firstFri13 ← 0
fri13Count ← 0
FOR m ← 1 TO 12
    holidays ← 0
    FOR d ← 1 TO DaysInMonth(year, m)
        IF IsHoliday(m, d) THEN holidays ← holidays + 1
    OUTPUT m, DaysInMonth(year, m), holidays, WeekdayName(DayNumber(year, m, 1) % 7)
    IF DayNumber(year, m, 13) % 7 == 4 THEN          // 13-ны өдөр Баасан
        fri13Count ← fri13Count + 1
        IF firstFri13 == 0 THEN firstFri13 ← m       // ЭХНИЙ тохирохыг хадгална
OUTPUT "Баасан гарагт таарсан 13-ны өдөр: " & fri13Count & " удаа, эхнийх нь " & firstFri13 & "-р сард"

// 5. Хоёр огноо харьцуулах
OUTPUT "1-р огноо:"
y1 ← ReadYear();  m1 ← ReadMonth();  d1 ← ReadDay(y1, m1)
OUTPUT "2-р огноо:"
y2 ← ReadYear();  m2 ← ReadMonth();  d2 ← ReadDay(y2, m2)
n1 ← DayNumber(y1, m1, d1)
n2 ← DayNumber(y2, m2, d2)
OUTPUT огноо бүр ба гарагийн нэр
IF n1 < n2 THEN       OUTPUT "1-р огноо " & (n2 − n1) & " хоногоор ӨМНӨ байна."
ELSE IF n1 > n2 THEN  OUTPUT "2-р огноо " & (n1 − n2) & " хоногоор ӨМНӨ байна."
ELSE                  OUTPUT "Хоёр огноо ИЖИЛ байна."
OUTPUT "Баярлалаа!"
```
