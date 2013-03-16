import java.util.Scanner;
 
public class Main{
    void run(){
 
	Scanner sc = new Scanner(System.in);
	while(sc.hasNext()){
	    int A = sc.nextInt();
	    int B = sc.nextInt();
	    if(A==0 && B==0) break;
	    //100 500 1000
 
	    int remaining = B-A;
 
	    int m1000 = 0;
	    int m500 = 0;
	    int m100 = 0;
	    while(remaining - 1000 >=0){
		m1000++;
		remaining -= 1000;
	    }
 
	    while(remaining - 500 >=0){
		m500++;
		remaining -= 500;
	    }
 
	    while(remaining - 100 >=0){
		m100++;
		remaining -= 100;
	    }
 
	    System.out.printf("%d %d %d\n",m100,m500,m1000);
 
	}
    }
     
    public static void main(String args[]){
	new Main().run();
    }
}
