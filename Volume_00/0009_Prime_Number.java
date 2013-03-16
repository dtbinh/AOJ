import java.util.Scanner;

public class Main{
    boolean[] isPrime;
    void run(){
	isPrime = new boolean[1000001];
	for(int i=0;i<=1000000;i++) isPrime[i] = true;

	isPrime[0] = false;
 	isPrime[1] = false;
  
	for(int i=2;i<=1000000;i++){
	    if(!isPrime[i]) continue;
	    for(int j=i+i;j<=1000000;j+=i){
		isPrime[j] = false;
	    }
	}
	Scanner sc = new Scanner(System.in);
 
	while(sc.hasNext()){
	    int n=sc.nextInt();
	    int count = 0;
	    for(int i=0;i<=n;i++){
		if(isPrime[i]) count++;
	    }
	    System.out.println(count);
	}
    }
    public static void main(String[] args){
	new Main().run();
    }
}