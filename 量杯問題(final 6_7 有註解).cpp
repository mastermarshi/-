#include<bits/stdc++.h>
using namespace std;
int n,k,start=0,end=0; //�]�m�ܼơAn���q�M�ơAk���ؼФ��q�Astart���_�l�����СAend������������ 
int tmp[6],full[6],arr[1000000][7]; //�]�m�}�C�A�}�C tmp���Ȯ��x�s�ܼƪ��a��
                                    // �}�C full���x�s�q�M�e�q���a�� 
                                    //�}�C arr���x�s�q�M�Ҧ��i�઺���q���a�� 

int push(){ //�]�m�@�Ө�ƦW�� "push" 
	
	for(int i=1;i<=n;i++) if(tmp[i]==k) return 2; //�p�G�}�C�����ȵ���k�ɡA�N�^��2 
	for(int i=0;i<=end;i++){
		int state = 0; //�]�m�ܼ� state����0 
		for(int j=1;j<=n;j++){
			if(tmp[j]!=arr[i][j]){  //�p�G�}�Ctmp�����Ȥ�����}�Carr�����ȡA�h�Ostate�ܬ�1�A�B�����j�� 
				state = 1;
				break;
			}
			
		}
		if(state==0) return 0; //�p�Gstate����0�ɡA�^��0 
	} 
	
	return 1; //�Y�Ҥ��ŦX�W�z���ԭz�A�h�^��1 
}


int main(){
	int i,j,match=0,ans=-1;
	cin>>n; //��J�q�M�ƶq 
	for(i=1;i<=n;i++){
		cin>>full[i]; // ��J�C�Ӷq�M�U�۪��e�q 
	}
	cin>>k; //��J�ؼФ��q 
	for(i=0;i<=n+1;i++) arr[0][i] = 0; //���q�M����Ҭ��Ū� 
	
	while(start<=end){  //�u�nstart���Ȥp��ε���end���ȡA�j��K�|����B�� 
		
		//case 1 : fill the cup to full
		for(i=1;i<=n;i++){
			bool dont = true;  //�]�m���L�ܼ� dont��true 
			if(arr[start][i]!=full[i]){  //�p�G�{�b�q�M�������q�����A�h�N��˺� 
				for(j=1;j<=n;j++) tmp[j] = arr[start][j];
				tmp[i]=full[i];
				dont = false;
			} 
			if(!dont){  // �p�G�ܼ� dont��false�A�h�I�s push��� 
				int state = push();  
				//try next or not
				if(state==2){   // �p�Gstate����2(�F��ؼФ��q)�A�h�N�B�J��+1�A�ñN�s�զXpush����ݫ���X�j��(break)  
					ans = arr[start][0] + 1; // �q��N�B�����X�Ӫ��զX����N+1�B �A �@��N+1�B  
					end++;  
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //�N�զX�[�J�}�Carr������ 
					arr[end][0] = ans; //�����F��ؼФ��q�һݪ��B�J�� 
					arr[end][6] = start; //�����W�@�ӨB�J���� 
					match = 1;
					break;
				}
				if(state==0) continue; //�p�Gstate����0�A�h���X�o��loop�A�~�����U�@��loop(continue) 
				if(state==1) { //�p�Gstate����1(�|����F�ؼФ��q)�A�h��end����+1(�N�s�զXpush��}�C����) 
					end++;
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l];  //�N�զX�[�J�}�Carr������ 
					arr[end][0] = arr[start][0] + 1;  //�N�B�J��+1 
					arr[end][6] = start;	//�O�����զX�O�q��N�ӲզX�����X�Ӫ�(�ΨӨD���|(�L�{)) 
				}	
			}
			
		} //end of case 1
		if(match==1) break; //�p�Gmatch����1�A�h���X�j�� 
		
		// case 2 : from i to j
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				for(int f=1;f<=n;f++) tmp[f] = arr[start][f];  //�N�զX�Ȧs��tmp��
				bool dont = true;   //�]�m���L�ܼ� dont��true  
				bool yes = ((i!=j)&&(tmp[i]!=0)&&(tmp[j]!=full[j])); 
				if(yes){ //�p�G��Ӷq�M���P�B�����q�M(i)�������q�����s�B�L���q�M(j)�|���Q�˺� �A�~����  
					//�ˤ��B�J�G �Ni�������ˤJj => �p�G�W�Lj���e�q�A�h�˦^i				              
					tmp[j] += tmp[i];   
					tmp[i] = 0;
					dont = false; //�N���L�ܼ� dont�אּfalse  
					if(tmp[j]>full[j]){   
						tmp[i] = tmp[j] - full[j];
						tmp[j] = full[j];
					}
					
				}
				if(!dont){ // �p�G�ܼ� dont��false�A�h�I�s push���  
				int state = push();
				//try next or not
				if(state==2){   // �p�Gstate����2(�F��ؼФ��q)�A�h�N�B�J��+1�A�B�N end����+1   
						ans = arr[start][0] + 1;
						end++;
						for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //�N�զX�[�J�}�Carr������ 
						arr[end][0] = ans; //�����F��ؼФ��q�һݪ��B�J�� 
						arr[end][6] = start; //�O�����զX�O�q��N�ӲզX�����X�Ӫ�(�ΨӨD���|(�L�{)) 
						match = 1;
						break;
					}
				if(state==0) continue;  //�p�Gstate����0�A�h���X�o��loop�A�~�����U�@��loop(continue)  
				if(state == 1) { //�p�Gstate����1(�|����F�ؼФ��q)�A�h��end����+1(�N�s�զXpush��}�C����)  
						end++;
						for(int l=1;l<=n;l++) arr[end][l] = tmp[l]; //�N�զX�[�J�}�Carr������
						arr[end][0] = arr[start][0] + 1; //�N�B�J��+1 
						arr[end][6] = start; //�O�����զX�O�q��N�ӲզX�����X�Ӫ�(�ΨӨD���|(�L�{)) 	
					}	
				}	
			}
			
			if(match==1) break;	
		}//end of case 2 
		if(match==1) break;	
		// case 3 : pour out all of it
		for(i=1;i<=n;i++){
			bool dont = true;  //�]�m���L�ܼ� dont��true   
			if(arr[start][i]!=0){  //�p�G�q�M�������A�h�N���˱��A�ñN���L�ܼ� dont�אּfalse  
				for(j=1;j<=n;j++) tmp[j] = arr[start][j];  //�N�զX�Ȧs��tmp�� 
				tmp[i]=0;
				dont = false;
			} 
			if(!dont){ // �p�G�ܼ� dont��false�A�h�I�s push���  
				int state = push();
				//try next or not
				if(state==0) continue;  //�p�Gstate����0�A�h���X�j��A�B��U�@���ܼ�  
				if(state == 1) { //�p�Gstake����1(�|����F�ؼФ��q)�A�h��end����+1  
					end++;
					for(int l=1;l<=n;l++) arr[end][l] = tmp[l];  //�N�զX�[�J�}�Carr������   
					arr[end][0] = arr[start][0] + 1; //�N�B�J��+1 
					arr[end][6] = start;	//�O�����զX�O�q��N�ӲզX�����X�Ӫ�(�ΨӨD���|(�L�{))
				}	
			}
			
		}// end of case 2
		if(match==1) break;
		start++;  //�Nstart����+1 
	}//end of while
	
	
	
	if(ans<0){ //�p�G�q�M�S���g���W�z�B�J�A�hans�N������l��(-1)�A�ó̫��X"���i�వ��" 
		cout<<"���i�వ��";
		return 0;
	}
	else{  //�_�h�K��X�Ҫ�O���B�J�ƩM�L�{ 
		cout<<"�B�J��: "<<ans<<"\n";
		cout<<"�L�{: \n";
	}
	
	//�H�U�������L�{(���q�զX)
	
	int step[ans+1][6]; //�ŧi�}�Cstep �A�����L�{(���q�զX) 
	for(int o=1;o<=n;o++) step[0][o] = 0; //��0�B�G�q�M�Ҫ� 
	for(int w=ans;w>0;w--){ // �q�̫�@�B(�F��ҨD���q)�}�l�O���A�z�L��M����parent�D�W�@�B 
		for(int o = 1;o<=n;o++){
			step[w][o] = arr[end][o];
		}
		end = arr[end][6]; //arr[i][6] �ΨӬ�������parent�O��x�� �C�Nend�令x�A���~��U�h 
	}
	
	for(int w=1;w<=ans;w++){
		for(int o=1;o<=n;o++){
			cout<<step[w][o]<<" "; // ��Xstep(�L�{�����q�զX) 
		}
		cout<<"\n";
	}
	
	// �H�U���ԲӨB�J (�ʧ@) 
	cout<<"\n";
	int p[ans+1][8]={0}; //�ŧip�ΨӰO���q�M�ܤơCp[i][0] ���ΡA p[i][1~5] �O���P�e�@�B�J�۴�(�U�q�M�ܤƶq)
						//p[i][6~7] �O�����ܤƪ��q�M�u�s���v(6�O�����q�ܤ֪��A7�h�O�ܦh��)
	for(int w=0;w<=ans-1;w++){ 
		int sum = 0; // sum ���u�`�ܤƶq�v�A��l�Ȭ�0 
		for(int o=1;o<=n;o++){ 
			p[w][o] = step[w+1][o] - step[w][o]; //�O���U�M�ܤƶq(��e�@�B�J) 
			sum += p[w][o]; // �N�ܤƶq�ۥ[ 
			if(p[w][o]!=0){		// �ܤƶq����0(���q���ܤ�) 
				if(p[w][o]<0) p[w][6] = o; // �p��0(�ܤ�)�A�O���bp[w][6] 
				else p[w][7] = o; //  �j��0(�ܦh)�A�O���bp[w][7] 
			}
		}
		if(sum>0) { //�`���q�ܤƤj��s => �N��N�Y�M�˺� 
			cout<<w+1<<". ���"<<p[w][7]<<"�M�˺�\n"; 
		}
		else if(sum<0){ //�`���q�ܤƤp��s => �N��N�Y�M�˥�  
			cout<<w+1<<". ���"<<p[w][6]<<"�M�˥�\n";
		}
		else{ // �`���q���ܡA�N���q ��"p[w][6]"�M �˨� ��"p[w][7]"�M
			int a = p[w][7]; //p[w][7]�����q�ܦh���q�M�u�s���v�C�]a = p[w][7]�A�h p[w][a] ���Ӷq�M���ܤƶq  
			cout<<w+1<<". �q��"<<p[w][6]<<"�M��"<<p[w][a]<<"���ɪ������"<<p[w][7]<<"�M\n";	
		}
	}

	return 0;
	
}
