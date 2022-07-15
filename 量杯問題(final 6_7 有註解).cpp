#include<bits/stdc++.h>
using namespace std;
int n,k,start=0,end=0; //設置變數，n為量杯數，k為目標水量，start為起始的指標，end為結束的指標 
int tmp[6],full[6],arr[1000000][7]; //設置陣列，陣列 tmp為暫時儲存變數的地方
                                    // 陣列 full為儲存量杯容量的地方 
                                    //陣列 arr為儲存量杯所有可能的水量的地方 

int push(){ //設置一個函數名為 "push" 
	
	for(int i=1;i<=n;i++) if(tmp[i]==k) return 2; //如果陣列中的值等於k時，就回傳2 
	for(int i=0;i<=end;i++){
		int state = 0; //設置變數 state等於0 
		for(int j=1;j<=n;j++){
			if(tmp[j]!=arr[i][j]){  //如果陣列tmp中的值不等於陣列arr中的值，則令state變為1，且結束迴圈 
				state = 1;
				break;
			}
			
		}
		if(state==0) return 0; //如果state等於0時，回傳0 
	} 
	
	return 1; //若皆不符合上述的敘述，則回傳1 
}


int main(){
	int i,j,match=0,ans=-1;
	cin>>n; //輸入量杯數量 
	for(i=1;i<=n;i++){
		cin>>full[i]; // 輸入每個量杯各自的容量 
	}
	cin>>k; //輸入目標水量 
	for(i=0;i<=n+1;i++) arr[0][i] = 0; //讓量杯原先皆為空的 
	
	while(start<=end){  //只要start的值小於或等於end的值，迴圈便會持續運行 
		
		//case 1 : fill the cup to full
		for(i=1;i<=n;i++){
			bool dont = true;  //設置布林變數 dont為true 
			if(arr[start][i]!=full[i]){  //如果現在量杯中的水量未滿，則將其裝滿 
				for(j=1;j<=n;j++) tmp[j] = arr[start][j];
				tmp[i]=full[i];
				dont = false;
			} 
			if(!dont){  // 如果變數 dont為false，則呼叫 push函數 
				int state = push();  
				//try next or not
				if(state==2){   // 如果state等於2(達到目標水量)，則將步驟數+1，並將新組合push到尾端後跳出迴圈(break)  
					ans = arr[start][0] + 1; // 從第N步延伸出來的組合為第N+1步 ， 共需N+1步  
					end++;  
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //將組合加入陣列arr的尾端 
					arr[end][0] = ans; //紀錄達到目標水量所需的步驟數 
					arr[end][6] = start; //紀錄上一個步驟為何 
					match = 1;
					break;
				}
				if(state==0) continue; //如果state等於0，則跳出這個loop，繼續執行下一個loop(continue) 
				if(state==1) { //如果state等於1(尚未到達目標水量)，則讓end的值+1(將新組合push到陣列尾端) 
					end++;
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l];  //將組合加入陣列arr的尾端 
					arr[end][0] = arr[start][0] + 1;  //將步驟數+1 
					arr[end][6] = start;	//記錄此組合是從第N個組合延伸出來的(用來求路徑(過程)) 
				}	
			}
			
		} //end of case 1
		if(match==1) break; //如果match等於1，則跳出迴圈 
		
		// case 2 : from i to j
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				for(int f=1;f<=n;f++) tmp[f] = arr[start][f];  //將組合暫存於tmp中
				bool dont = true;   //設置布林變數 dont為true  
				bool yes = ((i!=j)&&(tmp[i]!=0)&&(tmp[j]!=full[j])); 
				if(yes){ //如果兩個量杯不同且有水量杯(i)中的水量不為零且無水量杯(j)尚未被裝滿 ，才執行  
					//倒水步驟： 將i的水全倒入j => 如果超過j的容量，則倒回i				              
					tmp[j] += tmp[i];   
					tmp[i] = 0;
					dont = false; //將布林變數 dont改為false  
					if(tmp[j]>full[j]){   
						tmp[i] = tmp[j] - full[j];
						tmp[j] = full[j];
					}
					
				}
				if(!dont){ // 如果變數 dont為false，則呼叫 push函數  
				int state = push();
				//try next or not
				if(state==2){   // 如果state等於2(達到目標水量)，則將步驟數+1，且將 end的值+1   
						ans = arr[start][0] + 1;
						end++;
						for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //將組合加入陣列arr的尾端 
						arr[end][0] = ans; //紀錄達到目標水量所需的步驟數 
						arr[end][6] = start; //記錄此組合是從第N個組合延伸出來的(用來求路徑(過程)) 
						match = 1;
						break;
					}
				if(state==0) continue;  //如果state等於0，則跳出這個loop，繼續執行下一個loop(continue)  
				if(state == 1) { //如果state等於1(尚未到達目標水量)，則讓end的值+1(將新組合push到陣列尾端)  
						end++;
						for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //將組合加入陣列arr的尾端
						arr[end][0] = arr[start][0] + 1; //將步驟數+1 
						arr[end][6] = start; //記錄此組合是從第N個組合延伸出來的(用來求路徑(過程)) 	
					}	
				}	
			}
			
			if(match==1) break;	
		}//end of case 2 
		if(match==1) break;	
		// case 3 : pour out all of it
		for(i=1;i<=n;i++){
			bool dont = true;  //設置布林變數 dont為true   
			if(arr[start][i]!=0){  //如果量杯中有水，則將水倒掉，並將布林變數 dont改為false  
				for(j=1;j<=n;j++) tmp[j] = arr[start][j];  //將組合暫存於tmp中 
				tmp[i]=0;
				dont = false;
			} 
			if(!dont){ // 如果變數 dont為false，則呼叫 push函數  
				int state = push();
				//try next or not
				if(state==0) continue;  //如果state等於0，則跳出迴圈，運行下一個變數  
				if(state == 1) { //如果stake等於1(尚未到達目標水量)，則讓end的值+1  
					end++;
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l];  //將組合加入陣列arr的尾端   
					arr[end][0] = arr[start][0] + 1; //將步驟數+1 
					arr[end][6] = start;	//記錄此組合是從第N個組合延伸出來的(用來求路徑(過程))
				}	
			}
			
		}// end of case 2
		if(match==1) break;
		start++;  //將start的值+1 
	}//end of while
	
	
	
	if(ans<0){ //如果量杯沒有經歷上述步驟，則ans將維持初始值(-1)，並最後輸出"不可能做到" 
		cout<<"不可能做到";
		return 0;
	}
	else{  //否則便輸出所花費的步驟數和過程 
		cout<<"步驟數: "<<ans<<"\n";
		cout<<"過程: \n";
	}
	
	//以下為紀錄過程(水量組合)
	
	int step[ans+1][6]; //宣告陣列step ，紀錄過程(水量組合) 
	for(int o=1;o<=n;o++) step[0][o] = 0; //第0步：量杯皆空 
	for(int w=ans;w>0;w--){ // 從最後一步(達到所求水量)開始記錄，透過找尋它的parent求上一步 
		for(int o = 1;o<=n;o++){
			step[w][o] = arr[end][o];
		}
		end = arr[end][6]; //arr[i][6] 用來紀錄它的parent是第x項 。將end改成x，並繼續下去 
	}
	
	for(int w=1;w<=ans;w++){
		for(int o=1;o<=n;o++){
			cout<<step[w][o]<<" "; // 輸出step(過程中水量組合) 
		}
		cout<<"\n";
	}
	
	// 以下為詳細步驟 (動作) 
	cout<<"\n";
	int p[ans+1][8]={0}; //宣告p用來記錄量杯變化。p[i][0] 不用， p[i][1~5] 記錄與前一步驟相減(各量杯變化量)
						//p[i][6~7] 記錄有變化的量杯「編號」(6記錄水量變少的，7則是變多的)
	for(int w=0;w<=ans-1;w++){ 
		int sum = 0; // sum 為「總變化量」，初始值為0 
		for(int o=1;o<=n;o++){ 
			p[w][o] = step[w+1][o] - step[w][o]; //記錄各杯變化量(減前一步驟) 
			sum += p[w][o]; // 將變化量相加 
			if(p[w][o]!=0){		// 變化量不為0(水量有變化) 
				if(p[w][o]<0) p[w][6] = o; // 小於0(變少)，記錄在p[w][6] 
				else p[w][7] = o; //  大於0(變多)，記錄在p[w][7] 
			}
		}
		if(sum>0) { //總水量變化大於零 => 代表將某杯裝滿 
			cout<<w+1<<". 把第"<<p[w][7]<<"杯裝滿\n"; 
		}
		else if(sum<0){ //總水量變化小於零 => 代表將某杯倒光  
			cout<<w+1<<". 把第"<<p[w][6]<<"杯倒光\n";
		}
		else{ // 總水量不變，代表為從 第"p[w][6]"杯 倒到 第"p[w][7]"杯
			int a = p[w][7]; //p[w][7]為水量變多的量杯「編號」。設a = p[w][7]，則 p[w][a] 為該量杯之變化量  
			cout<<w+1<<". 從第"<<p[w][6]<<"杯倒"<<p[w][a]<<"公升的水到第"<<p[w][7]<<"杯\n";	
		}
	}

	return 0;
	
}
