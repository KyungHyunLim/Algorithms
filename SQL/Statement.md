# SQL 연습
#### 1. 모든 레코드 조회 ANIMAL_ID 순으로 정렬 (기본값: ASC)
```sql
SELECT * FROM ANIMAL_INS ORDER BY ANIMAL_ID;
```
#### 2. 특정 두 컬럼 조회, 역순으로 정렬
```sql
SELECT NAME, DATETIME FROM ANIMAL_INS ORDER BY ANIMAL_ID DESC
```
#### 3. 특정 컬럼의 특정 값을 가진 데이터 찾기
```sql
SELECT ANIMAL_ID, NAME FROM ANIMAL_INS WHERE INTAKE_CONDITION = "Sick" ORDER BY ANIMAL_ID
```
#### 4. 특정 컬럼의 특정 값이 아닌 데이터 찾기
```sql
SELECT ANIMAL_ID, NAME FROM ANIMAL_INS WHERE INTAKE_CONDITION != "Aged" ORDER BY ANIMAL_ID
```
#### 5. 여러 기준으로 정렬 하기
```sql
SELECT ANIMAL_ID, NAME, DATETIME FROM ANIMAL_INS ORDER BY NAME ASC, DATETIME DESC
```
#### 6. 상위 N개 레코드
```sql
SELECT NAME FROM ANIMAL_INS ORDER BY DATETIME LIMIT 1
```
#### 7. 최대값 구하기
```sql
SELECT MAX(DATETIME) FROM ANIMAL_INS
```
#### 8. 최솟값 구하기
```sql
SELECT MIN(DATETIME) FROM ANIMAL_INS
```
#### 9. 데이터의 수 구하기
```sql
SELECT COUNT(*) FROM ANIMAL_INS
```
#### 10. 중복제거 => DISTINCT, is not NULL => NULL 제거
```sql
SELECT COUNT(DISTINCT NAME) FROM ANIMAL_INS WHERE NAME is not NULL
```
```sql

```










