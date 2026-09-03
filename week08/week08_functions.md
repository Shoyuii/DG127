# Week 8 — Functions Reference

**Function Reference — `ex02_game_utils.c`**

| Function                                    | ทำหน้าที่                                                 | Returns                      |
| ------------------------------------------- | ------------------------------------------------------------------ | ---------------------------- |
| `int clamp(int value, int min, int max)`  | จำกัดค่า value ให้อยู่ระหว่าง min และ max | ค่าที่ clamp แล้ว  |
| `float lerp(float a, float b, float t)`   | Linear interpolation ระหว่าง a และ b ตาม t            | ค่าที่คำนวณได้ |
| `int randomRange(int min, int max)`       | สุ่มตัวเลขระหว่าง min และ max                  | ค่าสุ่ม               |
| `float percentOf(int current, int total)` | คำนวณเปอร์เซ็นต์                                   | ค่าเปอร์เซ็นต์ |

## คำถาม Reflection — Exercise 2

### 2.1 `clamp` — Pass by Value

**คำถาม:** ทำไม `hp` ใน `main()` ถึงยังเป็น 150 ทั้งที่ `value` ใน `clamp()` ถูกเขียนทับเป็น 100 ไปแล้ว?

**คำตอบ:** เพราะ hp = 150 ไม่ได้ทำอะไรเลยใน main() ส่วนที่ hp ในmain() เป็นตัวแปรในfunction clamp value > max max = value = 100 SafeHP จึงเท่ากับ 100 และแสดงออกมาเป็น 100

### 2.2 `lerp` — Local Scope

**คำถาม:** ทำไม `main()` ถึงมองไม่เห็นตัวแปร `result` ทั้งที่มันถูกประกาศไว้ในไฟล์เดียวกัน?

**คำตอบ:** ขอบเขตของตัวแปร scope ในภาษา C ไม่ได้ขึ้นกับว่าอยู่ “ไฟล์เดียวกัน” หรือไม่ แต่ขึ้นกับว่า ตัวแปรถูกประกาศอยู่ในบล็อก { } ไหน

### 2.3 `randomRange` — Pass by Value

**คำถาม:** ทำไม `diceMin` ใน `main()` ถึงยังเป็น 1 ทั้งที่ `min` ใน `randomRange()` ถูกบวกเพิ่มเป็น 101 ไปแล้ว?

**คำตอบ:** เพราะdiceMin ที่แสดงออกมาเป็น diceMin ที่อยู่ในmain() ส่วนที่คิดในfunctionคือ min ที่ดึงค่ามาจาก diceMin

### 2.4 `percentOf` — Pass by Value

**คำถาม:** ทำไม `score` ใน `main()` ถึงไม่เปลี่ยนเป็น 0 ตาม `current` ทั้งที่ `percentOf()` แก้ `current = 0;` ไปแล้ว?

**คำตอบ:** เพราะcurrent เป็นของfunction ซึ่งเป็นค่าที่ถูกส่งเข้ามา ไม่ใช่ตัวแปรใน main ดังนั้นการเปลี่ยนค่า current ภายในfunctionจะไม่มีผลต่อ score ใน main
