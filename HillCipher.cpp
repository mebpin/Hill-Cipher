//Hill Cipher
//Code by Bipin Timalsina
#include<iostream>
using namespace std;

class HillCipher{
	private: 
	// for  modulo  operation 
	int mod(int a, int b) {
  		int	c = a % b;
  		return (c < 0) ? c + b : c;
	}
		//to compute gcd
	int gcd(int a,int b){
		if(b==0)
			return a;
		else
			return gcd(b,a%b);
	}

	// to compute multiplicative inverse of b  in  modulo a
	int computeInverse(int a, int b){
		int n=a;
		int old_x = 1, x = 0;
	    int old_y = 0, y = 1;
	    int q, r;
	    while (b!=0){
	        q = a / b;//quotient 
	        r = a % b;//remainder
	        int temp = x;
	        x = old_x - q * x;
	        old_x = temp;
	        temp = y;
	        y = old_y - q * y;
	        old_y = temp;
	        a = b;
	        b = r;
    	}
    	int inverse = mod(old_y,n);
    	return  inverse;
	}
	public:
	int key[2][2];
	// taking key from user
	void getKey(){
 		cout<<"Enter the four elements of 2*2 key matrix:\n";
 		for(int i=0;i<2;i++){
 			for(int j =0; j<2;j++){
 				cin>>key[i][j]; 	
			 }
		 }
	 }
	 	//to check validity of key
	bool isValid(int a[2][2]){
		int d = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    	d = mod(d, 26);
    	//if determinant is coprime with 26 then 
		//the matrix in invertible in modulo 26  
		// and the key is valid
    	return (gcd(d,26)==1)&&d!=1?true:false;
	}
	 //taking message 
	string  getMessage(){
		string msg;
		cout<<"Enter the message:\n";
 		cin>> msg;

    	// message to uppercase
    	for (int i = 0; i < msg.length(); i++){
        	msg[i] = toupper(msg[i]);
    	}
    	if(msg.length()%2 != 0){
        	msg += "0";	
    	}
    	return msg;
    }
  // function performing encryption 	
    void encrypt(string msg){
    	// printig key matrix 
		cout<<"The  key matrix is : \n";
		for(int i = 0; i<2; i++){
			for(int j = 0; j<2; j++)
				cout<<key[i][j]<<" ";
		cout<<endl;
		}
    	string cipherText="";
    	int row= msg.length()/2;
    	//int matrix for msg
    	int msg2D[row][2];
		int p = 0;
		do{
			for(int i = 0;i<row;i++){
				for(int j = 0; j<2;j++){
					msg2D[i][j]= msg[p]-'A';
					p++;
				}
			}
		}while(p<msg.length());
	
    //	testing matrix
    cout<<"The Matrix of message "<<endl;
	  for(int i = 0; i < row; i++){
	       for (int j = 0; j < 2; j++){
	          cout << msg2D[i][j] << " ";
	       }
	       cout << endl;
	  }	
	cout<<"------------------------------ "<<endl;
	// in alphabetic form 
	  for(int i = 0; i < row; i++){
	       for (int j = 0; j < 2; j++){
	          cout << (char)(msg2D[i][j]+'A') << " ";
	       }
	       cout << endl;
	  }	
	  //multiplying message matrix with key matrix 
	  cout<<"Multiplying message with key  in mod 26 .. \n";
	int mult[row][2];
	int i,j,k,sum=0;
	  for (i = 0; i < row; i++) {
      for (j = 0; j < 2; j++) {
        for (k = 0; k < 2; k++) {
          sum = sum + msg2D[i][k] * key[k][j];
        }
        mult[i][j] = mod(sum,26);
        sum = 0;
      }
    }
 
    cout<<" The result of matrix multiplication is: \n "; 
    for (i = 0; i < row; i++) {
      for (j = 0; j < 2; j++)
        cout<<mult[i][j]<<" ";
      cout<<" \n ";
    }
 	//generating cipherText
    for (int i =0; i <row; i++){
    	for (int j = 0 ; j<2; j++){
    		char c = toupper(mult[i][j]+'A');
    		cipherText.push_back(c);
		}
	}
	cout<<"CipherText is : \n"<<cipherText; 
	} 
// function performing decryption 
	void decryption(string msg){
	 string plainText="";
    	int row= msg.length()/2;
    	//int matrix for msg
    	int msg2D[row][2];
		int p = 0;
		do{
			for(int i = 0;i<row;i++){
				for(int j = 0; j<2;j++){
					msg2D[i][j]= msg[p]-'A';
					p++;
				}
			}
		}while(p<msg.length());
    //	testing matrix
    cout<<"The Matrix of message "<<endl;
	  for(int i = 0; i < row; i++){
	       for (int j = 0; j < 2; j++){
	          cout << msg2D[i][j] << " ";
	       }
	       cout << endl;
	  }	
	cout<<"------------------------------ "<<endl;
	// in alphabetic form 
	  for(int i = 0; i < row; i++){
	       for (int j = 0; j < 2; j++){
	          cout << (char)(msg2D[i][j]+'A') << " ";
	       }
	       cout << endl;
	  }	
	  //computing determinant of key matrix
	  int d = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    	d = mod(d, 26);
    	cout<< " det= "<<d<<"\t";
	  //computing 1/det in mod 26
	  int oneByDet = computeInverse(26,d);
	  cout<< " oneByDet= "<<oneByDet<<"\n";
	 // computing inverse of key 
	 
	 	int keyInvrs[row][2]; 
	 	keyInvrs[0][0]= mod(oneByDet* key[1][1], 26);
	 	keyInvrs[1][1]= mod(oneByDet*key[0][0], 26);
		keyInvrs[0][1]= mod(oneByDet*-1*key[0][1], 26); 
		keyInvrs[1][0]= mod(oneByDet*-1*key[1][0], 26); 
	cout<<"The inverse key matrix is : \n";
	for(int i = 0; i<2; i++){
		for(int j = 0; j<2; j++)
			cout<<keyInvrs[i][j]<<" ";
		cout<<endl;
	}
	//multiplying  message matrix with inverse of key matrix 
	  cout<<"Multiplying message with inverse key  in mod 26 .. \n";
	
	int mult[row][2];
	int i,j,k,sum=0;
	  for (i = 0; i < row; i++) {
      for (j = 0; j < 2; j++) {
        for (k = 0; k < 2; k++) {
          sum = sum + msg2D[i][k] * keyInvrs[k][j];
        }
        mult[i][j] = mod(sum,26);
        sum = 0;
      }
    }
 
    cout<<" The result of matrix multiplication is: \n "; 
    for (i = 0; i < row; i++) {
      for (j = 0; j < 2; j++)
        cout<<mult[i][j]<<" ";
      cout<<" \n ";
    }
 	//generating plaintText
    for (int i =0; i <row; i++){
    	for (int j = 0 ; j<2; j++){
    		char c = toupper(mult[i][j]+'A');
    		plainText.push_back(c);
		}
	}
	cout<<"Plain Text is : \n"<<plainText; 	
	 	
	}
	
	
};
int main(){
	cout<<"=======	HILL CIPHER=========="<<endl<<endl;
	HillCipher hc;
	string message;
	int choice;
	char more='y';
	cout<<"=== ==== MENU ==== === ==="<<endl<<endl;
	while(more=='y'){
		cout<<"Enter your choice as following :\n";
		cout<<" Press 1 for encryption "<<endl;
		cout<<" Press 2 for decryption "<<endl;
		cout<<" Press 3 to cancel "<<endl;
		cout<<"=== === === === === === === === === === === ==="<<endl;
		cin>>choice;
		switch(choice){
			case 1: 
				hc.getKey();
				if(hc.isValid(hc.key)){
					cout<<"Your key is VALID go on..\n";
				}else{
					cout<<"Your key is INVALID try again..\n";
					exit(0);
				}
				message= hc.getMessage();
				hc.encrypt(message);
				break;
			case 2: 
				hc.getKey();
				if(hc.isValid(hc.key)){
					cout<<"Your key is VALID go on..\n";
				}else{
					cout<<"Your key is INVALID try again..\n";
					exit(0);
				}
				message= hc.getMessage();
				hc.decryption(message);
				break;
			case 3: 
				exit(0);
			default:
				cout<<"Invalid choice!!"<<endl;	
		}
	cout<<"\n\n Do you want to continue?(press y if you want)"<<endl;
	cin>>more;
	}	
	return 0;
}
