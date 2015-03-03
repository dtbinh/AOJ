import java.util.Scanner;
import java.math.BigInteger;

class Main {
    public static void main(String args[]){
	Scanner sc = new Scanner(System.in);

	String units[] = {"Man","Oku","Cho","Kei","Gai","Jo","Jou","Ko","Kan",
			  "Sei","Sai","Gok","Ggs","Asg","Nyt","Fks","Mts"};
        while(sc.hasNext()){
            String m = sc.next();
	    int n = sc.nextInt();
	    if(n == 0) break;
	    BigInteger bi = new BigInteger(m);
	    bi = bi.pow(n);
	    for(int i = 68; i >= 4; i -= 4){
		BigInteger div = new BigInteger("10");
		if(bi.divide(div.pow(i)).signum() == 1){
		    System.out.printf("%s%s",bi.divide(div.pow(i)),units[i / 4 - 1]);
		    bi = bi.remainder(div.pow(i));
		}
	    }
	    if(bi.signum() == 1){
		System.out.print(bi);
	    }
	    System.out.println();
        }
    }
}
