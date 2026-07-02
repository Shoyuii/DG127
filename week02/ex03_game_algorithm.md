โจทย์ A

```mermaid
flowchart TD
Start([Start]) --> Input[/รับ player_attack, enemy_defense,
enemy_hp/]
Input --> Calc["damage = max(player_attack - enemy_defense,
1)"]
Calc --> Reduce["enemy_hp = enemy_hp - damage"]
Reduce --> D1{enemy_hp <= 0?}
D1 -->|Yes| Win[/แสดง Victory!/]
D1 -->|No| Show[/แสดง enemy_hp ที่เหลือ/]
Win & Show --> End([End])
```

---

โจทย์ B

```mermaid
flowchart TD
Start([Start]) --> Input[/Input current_xp, xp_needed, level/]
Input --> A{current_xp >= xp_needed?}
A -->|Yes| B[level = level + 1]
B --> C[xp_needed = xp_needed x 1.5]
C --> D[curret_xp = 0]
A -->|No| Output[/Output level and current_xp/]
D --> Output
Output --> End([End])
```

---

โจทย์ C

```mermaid
flowchart TD
Start([Start]) --> A[pos = A, dir = forward]
A --> B{ระยะถึง player < 100?}
B --> |Yes| C[/chase player/]
C --> End([End])
B --> D[เลื่อน enemy ตาม dir]
D --> E{ถึงจุด B?}
E --> |Yes| F[dir = กลับไป A]
F --> B
E --> |No| G{ถึงจุด A?}
G --> |No| B
G --> |Yes| H[dir = ไปหน้า B]
H --> B
```
