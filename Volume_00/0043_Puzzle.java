import java.util.Scanner;
import java.util.Collections; 
import java.util.ArrayList; 
 
public class Main{
    void run(){
	Scanner sc = new Scanner(System.in);
	while(sc.hasNext()){
	    String str = sc.nextLine();
 
	    ArrayList<Character> tmp_e = new ArrayList<Character>();
	    char[] freq = new char[255];
	    for(int i=0;i<str.length();i++){
		tmp_e.add(str.charAt(i));
		freq[str.charAt(i)]++;
	    }
 
	    ArrayList<Character> res = new ArrayList<Character>();
	    for(char lastChar='1';lastChar<='9';lastChar++){
		if(freq[lastChar] >= 4) continue;
		ArrayList<Character> e  = new ArrayList<Character>(tmp_e);
		e.add(lastChar);
 
		Collections.sort(e);
		// System.out.println(e);
		ArrayList<Integer> JantoList = findJanto(e,0);
		// printBitArray(JantoList,14);
		for(int i=0;i<JantoList.size();i++){
		    ArrayList<Integer> cand = findKotsu(e,JantoList.get(i));
 
		    // System.out.println("after find kotsu");
		    // printBitArray(cand,14);
 
		    for(int S=0;S<=(1<<cand.size())-1;S++){
			ArrayList<Integer> cand2 = new ArrayList<Integer>();
			for(int j=0;j<cand.size();j++){
			    if((S & (1<<j)) > 0){
				cand2.add(cand.get(j));
			    }
			}
 
			if(!isIntersect(cand2,14)){
			    int visited = JantoList.get(i);
			    for(int k=0;k<cand2.size();k++){
				visited |= cand2.get(k);
			    }
 
			    // System.out.println("after fill kotsu");
			    // printBit(visited,14);
			    // System.out.println(fillShuntsu(e,visited));
			    if(fillShuntsu(e,visited)){
				res.add(lastChar);
				// System.out.println(lastChar);
				break;
			    }
			}
		    }
		    //System.out.println(cand);
         
		}
	    }
         
	    show(res);
	}
    }
 
    void show(ArrayList<Character> e){
	Collections.sort(e);
	int[] freq = new int[255];
	ArrayList<Character> res = new ArrayList<Character>();
     
	for(int i=0;i<e.size();i++){
	    if(freq[e.get(i)] > 0) continue;
	    freq[e.get(i)]++;
	    res.add(e.get(i));
	}
 
	if(res.size() == 0){
	    System.out.println(0);
	    return;
	}
 
	for(int i = 0; i<res.size(); i++){
	    System.out.printf("%s%c",i==0 ? "" : " ",res.get(i));
	}
	System.out.println();
    }
    void printBitArray(ArrayList<Integer> e,int w){
	for(int i=0;i<e.size();i++){
	    printBit(e.get(i),w);
	}
    }
    void printBit(int num,int w){
	for(int i=0;i<w;i++){
	    if((num & (1<<i)) > 0){
		System.out.print("1");
	    }
	    else{
		System.out.print("0");
	    }
	}
	System.out.println();
    }
 
    ArrayList<Integer> findJanto(ArrayList<Character> e,int visited){
	ArrayList<Integer> res = new ArrayList<Integer>();
	for(int base=1;base<=9;base++){
	    for(int i=0;i+1<e.size();i++){
		int tmp = visited;
		if(e.get(i) == base + '0'
		   && e.get(i+1) == base + '0'){
		    tmp |= (1<<i);
		    tmp |= (1<<(i+1));
		    res.add(tmp);
		    //System.out.println(e.get(i));
		}
	    }
	}
 
	//System.out.println(res);
	return res;
    }
 
    boolean isIntersect(ArrayList<Integer> e,int width){
	for(int i=0;i<e.size();i++){
	    for(int j=i+1;j<e.size();j++){
		for(int k=0;k<width;k++){
		    int a = e.get(i);
		    int b = e.get(j);
 
		    if(((a & (1<<k))
			& (b & (1<<k))) > 0){
			return true;
		    }
		}
	    }
	}
	return false;
    }
 
    ArrayList<Integer> findKotsu(ArrayList<Character> e,int visited){
	ArrayList<Integer> res = new ArrayList<Integer>();
	for(int base=1;base<=9;base++){
	    for(int i=0;i+2<e.size();i++){
		if((
		    (visited & (1<<i))
		    | (visited & (1<<(i+1)))
		    | (visited & (1<<(i+2)))
		    ) > 0) continue;
		int tmp = 0;
		if(e.get(i) == base + '0'
		   && e.get(i+1) == base + '0'
		   && e.get(i+2) == base + '0'){
		    tmp |= (1<<i);
		    tmp |= (1<<(i+1));
		    tmp |= (1<<(i+2));
		    res.add(tmp);
		    //System.out.println(e.get(i));
		}
	    }
	    //System.out.println(res);
	}
	return res;
    }
 
    boolean fillShuntsu(ArrayList<Character> e,int visited){
     
	for(int i=0;i<e.size();i++){
	    int count = 0;
	    if((visited & (1<<i)) > 0) continue;
	    int tmp = visited;
	    int first = e.get(i);
	    count++;
	    tmp |= (1<<i);
	    for(int j=i+1;j<e.size();j++){
		if((visited & (1<<j)) > 0) continue;
		if(first + 1 == e.get(j)
		   && (tmp & (1<<j)) == 0
		   && count == 1){
		    tmp |= (1<<j);
		    count++;
		}
		if(first + 2 == e.get(j)
		   && (tmp & (1<<j)) == 0
		   && count == 2){
		    tmp |= (1<<j);
		    count++;
		    break;
             
		}
		if(first + 2 < e.get(j)){
		    count = 0;
		    break;
		}
	    }
 
	    if(count == 3){
		visited = tmp;
	    }
	}
	//System.out.println(res);
	return (visited == ((1<<14)-1));
    }
 
    public static void main(String args[]){
	new Main().run();
    }
}