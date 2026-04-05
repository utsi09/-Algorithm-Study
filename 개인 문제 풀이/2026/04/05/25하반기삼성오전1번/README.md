https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/delivery-service/description

---
소요시간 : 5시간

블록을 만들고 r1,r2, c1,c2

충돌 검사하고 이동하고 관리하는 삼성 기출 문제이다.

```cpp
for(Box& tmp_b : boxes){
```

&로 실제 객체를 가져와서 is_remove 를 수정해야 하는데 &없이 복사본에 수정하고 있으니
계속 같은거만 검사해서 헤멨다.

다음에 한번더 풀어봐야할것같다.
