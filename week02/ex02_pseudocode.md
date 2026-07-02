BEGIN [โจทย์A]
	INPUT score
	IF score >= 80 THEN
		 grade = "A"

    ELSE IF score >= 70 THEN
		grade = "B"

    ELSE IF score >= 60 THEN
		grade = "C"

    ELSE IF score >= 50 THEN
		grade = "D"

    ELSE grade = "F"
	
	END IF
	OUTPUT grade

END

---

BEGIN [โจทย์B]
	INPUT "a" and "b"
	IF a >b THEN
		Output a

    ELSE Output b

    END IF

END

---

BEGIN[โจทย์C]
	INPUT N
	i = 1
	WHILE i <= N DO
    		Print i
    		i = i + 1

    END WHILE

END
