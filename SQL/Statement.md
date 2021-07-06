# SQL 연습
### SELECT
#### 1. 모든 레코드 조회 ANIMAL_ID 순으로 정렬 (기본값: ASC)
```sql
SELECT * 
FROM ANIMAL_INS 
ORDER BY ANIMAL_ID;
```
#### 2. 특정 두 컬럼 조회, 역순으로 정렬
```sql
SELECT NAME, DATETIME 
FROM ANIMAL_INS 
ORDER BY ANIMAL_ID DESC
```
#### 3. 특정 컬럼의 특정 값을 가진 데이터 찾기
```sql
SELECT ANIMAL_ID, NAME 
FROM ANIMAL_INS 
WHERE INTAKE_CONDITION = "Sick" 
ORDER BY ANIMAL_ID
```
#### 4. 특정 컬럼의 특정 값이 아닌 데이터 찾기
```sql
SELECT ANIMAL_ID, NAME 
FROM ANIMAL_INS
WHERE INTAKE_CONDITION != "Aged" 
ORDER BY ANIMAL_ID
```
#### 5. 여러 기준으로 정렬 하기
```sql
SELECT ANIMAL_ID, NAME, DATETIME 
FROM ANIMAL_INS 
ORDER BY NAME ASC, DATETIME DESC
```
#### 6. 상위 N개 레코드
```sql
SELECT NAME 
FROM ANIMAL_INS 
ORDER BY DATETIME LIMIT 1
```
#### 7. 최대값 구하기
```sql
SELECT MAX(DATETIME) 
FROM ANIMAL_INS
```
### SUM, MAX, MIN
#### 8. 최솟값 구하기
```sql
SELECT MIN(DATETIME) 
FROM ANIMAL_INS
```
#### 9. 데이터의 수 구하기
```sql
SELECT COUNT(*) 
FROM ANIMAL_INS
```
#### 10. 중복제거 => DISTINCT, is not NULL => NULL 제거
```sql
SELECT COUNT(DISTINCT NAME) 
FROM ANIMAL_INS 
WHERE NAME is not NULL
```
### Group By
#### 11. 고양이와 개는 각각 몇마리 있는가?
```sql
SELECT ANIMAL_TYPE, COUNT(ANIMAL_TYPE) 
FROM ANIMAL_INS 
WHERE ANIMAL_TYPE = 'Cat' or ANIMAL_TYPE = 'Dog' 
GROUP BY ANIMAL_TYPE 
ORDER BY ANIMAL_TYPE
```
#### 12. 같은 이름이 두개 이상, 이름이 없으면 제외, 결과는 이름 순
```sql
SELECT NAME, COUNT(NAME) 
FROM ANIMAL_INS 
WHERE NAME is not NULL 
Group By NAME
HAVING COUNT(NAME) >= 2 
ORDER By NAME
```
#### 13. 09:00부터 19:59까지, 각 시간대별로 입양이 몇 건이나 발생했는지 조회
```sql
SELECT HOUR(DATETIME) AS HOUR, COUNT(DATETIME)
FROM ANIMAL_OUTS
GROUP BY HOUR
HAVING HOUR BETWEEN 9 AND 19
ORDER BY HOUR
```
#### 14. 0시부터 23시까지, 각 시간대별로 입양이 몇 건이나 발생했는지 조회하는 SQL문을 작성해주세요. 이때 결과는 시간대 순으로 정렬 <없으면 0 으로 표시>
```sql
WITH RECURSIVE TIME as (
    SELECT 0 as HOUR # 초기 HOUR 값 설정
    UNION ALL # 위, 아래 쿼리 값 연산
    SELECT HOUR+1 FROM TIME # HOUR를 하나씩 증가 시킴
    WHERE HOUR < 23 # RECURSIVE 멈춤 조건
)
SELECT HOUR, COUNT(DATETIME)
FROM TIME
    left join ANIMAL_OUTS ON HOUR = HOUR(DATETIME)
GROUP By HOUR
ORDER BY HOUR
```
#### 15.







