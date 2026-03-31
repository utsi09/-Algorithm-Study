Q. N과 N개의 자연수가 주어진다. 여기서 몇개의 숫자를 골라 합을
mod 11을 했을 때 나오는 가장 큰수를 구하라.
입력:
10
24 35 38 40 49 59 60 67 83 98
출력:
10

---

# 내 생각

```cpp
void go(int idx, int sum){
    if(idx == N){
        ret = max(ret, sum % 11);
        // cout << ret << endl;
        return;
    }
    go(idx+1, sum + v[idx]); go(idx+1, sum);
}
```
 처음에 N-1로 해야되나 생각했는데 그렇게 되면 마지막값은 누적이 안된다 그러므로 N과 같을때 로직 시작
 return  go(idx+1, sum + v[idx])+ go(idx+1, sum);
 로 cnt 1씩 더해서 카운트햇던 이전과는 달리 기저사례 도달할때까지 저렇게 하는 방식으로 하는게 차이점
