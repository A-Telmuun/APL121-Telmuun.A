/*
 * APL121 · Бие даалт №1 — Code Quest
 * Сэдэв №29: Хуанли хэвлэгч
 *
 * Он, сар оруулахад өндөр жил эсэх, сарын хоногийн тоог тодорхойлж,
 * тухайн сарын хуанлийг 7 баганаар хэвлэнэ. Дараа нь жилийн 12 сарын
 * тойм хүснэгт гаргаж, "Баасан гарагт таарсан 13-ны өдөр"-ийг хайна.
 * Эцэст нь хоёр огноо оруулж, аль нь өмнө болохыг олно.
 *
 * Тогтоосон дүрмүүд (README.md-д дэлгэрэнгүй):
 *   - Он 1900–2100 хооронд байна.
 *   - 7 хоног ДАВАА гарагаас эхэлнэ (Монгол заншил).
 *   - 1900 оны 1-р сарын 1 бол Даваа гараг гэдгийг эхлэл болгоно.
 *   - Тогтмол огноотой нийтээр амрах баярын өдрийг * тэмдгээр тэмдэглэнэ.
 *
 * Компайл:    gcc -Wall -Wextra -o calendar main.c
 * Ажиллуулах: ./calendar
 *
 * Тайлбар: Flowgorithm-ийн функц бүр энд ижил утгатай C функц болсон.
 */
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MIN_YEAR 1900
#define MAX_YEAR 2100

/* Тоо унших. Үсэг гэх мэт буруу оролт орвол -1 буцааж,
 * мөрийн үлдсэн хэсгийг цэвэрлэнэ. Оролт дуусвал программыг зогсооно. */
int read_int(void)
{
    int value;
    int c;
    int result = scanf("%d", &value);

    if (result == EOF) {
        printf("\nОролт дууслаа.\n");
        exit(1);
    }
    if (result != 1) {
        value = -1;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* буруу тэмдэгтүүдийг алгасна */
        }
    }
    return value;
}

/* Flowgorithm: IsLeap — Григорийн тооллын өндөр жилийн дүрэм */
int is_leap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/* Flowgorithm: DaysInMonth — else-if шат */
int days_in_month(int year, int month)
{
    int days;

    if (month == 2) {
        if (is_leap(year)) {
            days = 29;
        } else {
            days = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        days = 30;
    } else {
        days = 31;
    }
    return days;
}

/* Flowgorithm: DayNumber — 1900-01-01-ээс хойш өнгөрсөн хоногийн тоо.
 * Томьёо цээжлэхгүйгээр жил, сар бүрийн хоногийг давталтаар нэмнэ. */
int day_number(int year, int month, int day)
{
    int total = 0;
    int y;
    int m;

    for (y = MIN_YEAR; y <= year - 1; y++) {
        if (is_leap(y)) {
            total = total + 366;
        } else {
            total = total + 365;
        }
    }
    for (m = 1; m <= month - 1; m++) {
        total = total + days_in_month(year, m);
    }
    total = total + day - 1;
    return total;
}

/* Flowgorithm: WeekdayName — 0 = Даваа ... 6 = Ням */
const char *weekday_name(int weekday)
{
    const char *name;

    if (weekday == 0) {
        name = "Даваа";
    } else if (weekday == 1) {
        name = "Мягмар";
    } else if (weekday == 2) {
        name = "Лхагва";
    } else if (weekday == 3) {
        name = "Пүрэв";
    } else if (weekday == 4) {
        name = "Баасан";
    } else if (weekday == 5) {
        name = "Бямба";
    } else {
        name = "Ням";
    }
    return name;
}

/* Flowgorithm: IsHoliday — тогтмол огноотой нийтээр амрах өдрүүд */
int is_holiday(int month, int day)
{
    return (month == 1 && day == 1)                  /* Шинэ жил                   */
        || (month == 3 && day == 8)                  /* Эмэгтэйчүүдийн баяр        */
        || (month == 6 && day == 1)                  /* Хүүхдийн баяр              */
        || (month == 7 && day >= 11 && day <= 15)    /* Үндэсний их баяр наадам    */
        || (month == 11 && day == 26)                /* Үндэсний эрх чөлөөний өдөр */
        || (month == 12 && day == 29);               /* Тусгаар тогтнолын өдөр     */
}

/* Flowgorithm: ReadYear — do-while оролтын шалгалт */
int read_year(void)
{
    int year;

    do {
        printf("Он оруулна уу (%d-%d): ", MIN_YEAR, MAX_YEAR);
        year = read_int();
        if (year < MIN_YEAR || year > MAX_YEAR) {
            printf("Алдаа: он %d-%d хооронд байх ёстой!\n", MIN_YEAR, MAX_YEAR);
        }
    } while (year < MIN_YEAR || year > MAX_YEAR);
    return year;
}

/* Flowgorithm: ReadMonth */
int read_month(void)
{
    int month;

    do {
        printf("Сар оруулна уу (1-12): ");
        month = read_int();
        if (month < 1 || month > 12) {
            printf("Алдаа: сар 1-12 хооронд байх ёстой!\n");
        }
    } while (month < 1 || month > 12);
    return month;
}

/* Flowgorithm: ReadDay — хоногийн дээд хязгаар нь тухайн сараас хамаарна */
int read_day(int year, int month)
{
    int day;
    int max_day = days_in_month(year, month);

    do {
        printf("Өдөр оруулна уу (1-%d): ", max_day);
        day = read_int();
        if (day < 1 || day > max_day) {
            printf("Алдаа: өдөр 1-%d хооронд байх ёстой!\n", max_day);
        }
    } while (day < 1 || day > max_day);
    return day;
}

/* Flowgorithm: PrintCalendar — Main-аас Call блокоор дуудагддаг процедур */
void print_calendar(int year, int month)
{
    int days = days_in_month(year, month);
    int start_col = day_number(year, month, 1) % 7;   /* 1-ний өдрийн гараг */
    int column;
    int day_no;

    printf("\n      %d оны %d-р сар\n", year, month);
    printf(" Да  Мя  Лх  Пү  Ба  Бя  Ня\n");

    /* 1-ний өдөр хүртэлх хоосон нүднүүд */
    for (column = 0; column < start_col; column++) {
        printf("    ");
    }

    column = start_col;
    for (day_no = 1; day_no <= days; day_no++) {
        printf("%3d", day_no);
        if (is_holiday(month, day_no)) {
            printf("*");
        } else {
            printf(" ");
        }
        column = column + 1;
        if (column == 7) {          /* Ням гарагийн дараа шинэ мөр */
            printf("\n");
            column = 0;
        }
    }
    if (column != 0) {
        printf("\n");
    }
    printf("(* = нийтээр амрах баярын өдөр)\n");
}

int main(void)
{
    int year;
    int month;
    int m;
    int d;
    int holidays;
    int first_friday13;
    int friday13_count;
    int y1, m1, d1;
    int y2, m2, d2;
    int n1, n2;

#ifdef _WIN32
    SetConsoleOutputCP(65001);   /* Windows консолд кирилл үсэг харуулах */
    SetConsoleCP(65001);
#endif

    printf("=== ХУАНЛИ ХЭВЛЭГЧ (Сэдэв №29) ===\n");

    /* 1. Оролт: он, сар */
    year = read_year();
    month = read_month();

    /* 2. Өндөр жил ба сарын хоног */
    if (is_leap(year)) {
        printf("%d он: өндөр жил (366 хоног)\n", year);
    } else {
        printf("%d он: энгийн жил (365 хоног)\n", year);
    }
    printf("%d-р сар %d хоногтой\n", month, days_in_month(year, month));

    /* 3. Сарын хуанли (Flowgorithm: Call PrintCalendar) */
    print_calendar(year, month);

    /* 4. Жилийн тойм хүснэгт + "Баасан 13"-ыг давталтаар хайх */
    printf("\n--- %d оны сар бүрийн тойм ---\n", year);
    printf(" Сар  Хоног  Баяр   Эхлэх гараг\n");
    first_friday13 = 0;
    friday13_count = 0;
    for (m = 1; m <= 12; m++) {
        holidays = 0;
        for (d = 1; d <= days_in_month(year, m); d++) {
            if (is_holiday(m, d)) {
                holidays = holidays + 1;
            }
        }
        printf("%4d %6d %5d   %s\n", m, days_in_month(year, m), holidays,
               weekday_name(day_number(year, m, 1) % 7));

        /* 13-ны өдөр Баасан (4) гарагт таарсан эсэх */
        if (day_number(year, m, 13) % 7 == 4) {
            friday13_count = friday13_count + 1;
            if (first_friday13 == 0) {
                first_friday13 = m;      /* эхний тохирохыг хадгална */
            }
        }
    }
    printf("Баасан гарагт таарсан 13-ны өдөр: %d удаа, эхнийх нь %d-р сард\n",
           friday13_count, first_friday13);

    /* 5. Хоёр огноо харьцуулах */
    printf("\n--- Хоёр огноо харьцуулах ---\n");
    printf("1-р огноо:\n");
    y1 = read_year();
    m1 = read_month();
    d1 = read_day(y1, m1);
    printf("2-р огноо:\n");
    y2 = read_year();
    m2 = read_month();
    d2 = read_day(y2, m2);

    n1 = day_number(y1, m1, d1);
    n2 = day_number(y2, m2, d2);

    printf("%d-%d-%d (%s), %d-%d-%d (%s)\n",
           y1, m1, d1, weekday_name(n1 % 7), y2, m2, d2, weekday_name(n2 % 7));
    if (n1 < n2) {
        printf("1-р огноо %d хоногоор ӨМНӨ байна.\n", n2 - n1);
    } else if (n1 > n2) {
        printf("2-р огноо %d хоногоор ӨМНӨ байна.\n", n1 - n2);
    } else {
        printf("Хоёр огноо ИЖИЛ байна.\n");
    }

    printf("\nБаярлалаа!\n");
    return 0;
}
