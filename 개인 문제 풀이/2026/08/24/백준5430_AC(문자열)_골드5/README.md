벡터 reserve와 erase로 풀면 10만 x 10만이기 때문에 wa가 나온다

모든 리버스를 bool 을 비트 전환하면서 최종 상태 전환하고

reverse 상태에 따라 삭제된 인덱스를 오른쪽 int 왼쪽 int 나눠서 저장한다
