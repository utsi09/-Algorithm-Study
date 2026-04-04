https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/ai-robot/description

---

소요시간 : 4~5시간 

1. bfs 인자 robot_idx로 받아놓고 열좌표 j를 로봇 번호로 써서 헤멤 함수 인자 제대로 확인하기 , 그리고 인자는 turn r_idx ,r,c,dir 처럼 명확히 분리해서 쓰기

2. 전역변수로 로봇 개수 k로 받은거 계속 써야하는데 반복문 인자로 또 k로 써서 헤멤

3. 격자마다 청소할 수 있는 최대 먼지량은 20입니다 햇는데 max(adj[ny][nx], 20)로로 짜서 먼지가 0이어도 20을 가져오는 기적의 청소기를 만들어버림

4. 동시 발생은 무조건 복사본 기준으로 tmp-adj복사 잘해놓고 adj에 원본값을 더함 그래서 뒤로 미세하게 커짐

5. 아예갈수있는 먼지가 없을때 best_robots.empty() 체크를 안해서 초기값 1e8로 로봇이 우주로 텔레포트함 중요

6. 변수 초기화 위치 두번 확인하기 int same_pos = 0; 이거 하나 for(int d=0; d<4; d++) 바깥에 뒀다가, 첫 번째 방향에서 로봇 발견했다고 남은 3방향까지 다 막혀버려서 로봇들 통나무 됨.
