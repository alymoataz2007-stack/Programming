public class state {
    String name;
    int[] next_states;
    int[] outputs;
    public state(String name,int inputs_number){
      this.name=name;
      int numcombinations=(int)Math.pow(2,inputs_number);
      this.next_states= new int[numcombinations];
      this.outputs=new int[numcombinations];
    }
}
class cell{
    boolean iscrossed=false;
    int[][]dependencies;
    public cell(int inputs_number){
        int numcombinations=(int)Math.pow(2,inputs_number);
        this.dependencies=new int[numcombinations][2];
    }
}
