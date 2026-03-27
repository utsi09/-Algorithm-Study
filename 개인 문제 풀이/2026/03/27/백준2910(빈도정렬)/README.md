https://www.acmicpc.net/problem/2910

---

map을 참조하면 객체가 생성되는 것을 이용한 문제 풀이

참조 횟수가 같으면 누가 먼저 참조됐는지를 비교하기 위한 map<int,int> mp_first도 만드는것이 핵심

또한 커스텀 sort 함수를 사용해야 한다.

기본적으로 참조횟수가 많은 놈이 왼쪽으로 가야되기 때문에 a.first > b.first 를 사용하였고

둘이 같은 경우에는 mp_first를 비교하여 더 먼저 참조된 놈이 왼쪽으로 가야되기 때문에 더 작은 녀석을 왼쪽으로 보내는 

```cpp
return mp_first[a.second] < mp_first[b.second] 
```

을 사용함
