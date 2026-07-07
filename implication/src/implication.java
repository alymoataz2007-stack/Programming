import java.util.Scanner;

public class implication {
    public static void main(String[] args){
        Scanner scan=new Scanner(System.in);
        System.out.println("Enter number of states");
        int states_num=scan.nextInt();
        System.out.println("Please Enter number of external inputs");
        int inputs_number=scan.nextInt();
        int numcombinations=(int)Math.pow(2,inputs_number);
        state[]states=new state[states_num];
        for(int i=0;i<states_num;i++){
            states[i]=new state("S"+i,inputs_number);
            System.out.println("Filling state S"+i);
            for(int k=0;k<numcombinations;k++){
                String combo=Integer.toBinaryString(k);
                while(combo.length()<inputs_number)
                    combo="0"+combo;
                System.out.println("Enter next state for input "+combo+" ex: enter 2 for S2");
                states[i].next_states[k]=scan.nextInt();
                System.out.println("Enter output for input "+combo+" ex: enter 2 for S2");
                states[i].outputs[k]= scan.nextInt();

            }
        }
        cell [][]table=new cell[states_num][states_num];
        for(int i=1;i<states_num;i++){
            for(int j=0;j<i;j++){
                table[i][j]=new cell(inputs_number);
                for(int k=0;k<numcombinations;k++){
                    table[i][j].dependencies[k][0]=states[i].next_states[k];
                    table[i][j].dependencies[k][1]=states[j].next_states[k];
                }

            }
        }

       for(int i=1;i<states_num;i++){
           for(int j=0;j<i;j++){
               for(int k=0;k<numcombinations;k++){
                if(states[i].outputs[k]!=states[j].outputs[k]){
                    table[i][j].iscrossed=true;
                    break;
                }
               }
           }
       }
       boolean changed;
       do{
           changed=false;
           for(int i=1;i<states_num;i++){
               for(int j=0;j<i;j++){
                   if(!table[i][j].iscrossed){
                       for(int k=0;k<numcombinations;k++){
                           int nextA=table[i][j].dependencies[k][0];
                           int nextB=table[i][j].dependencies[k][1];
                           if(nextA!=nextB){
                               int row=Math.max(nextA,nextB);
                               int col=Math.min(nextA,nextB);
                               if(table[row][col].iscrossed){
                                   table[i][j].iscrossed=true;
                                   changed=true;
                                   break;
                               }
                           }
                       }
                   }
               }
           }
       }while(changed);
        System.out.println("Minimization Results");
        boolean[]processed=new boolean[states_num];
        boolean foundgroups=false;
        for(int i=0;i<states_num;i++){
            if(!processed[i]){
                boolean hasequivalent=false;
                for(int j=0;j<states_num;j++){
                    if(i!=j){
                        int row=Math.max(i,j);
                        int col=Math.min(i,j);
                        if(!table[row][col].iscrossed){
                            hasequivalent=true;
                            break;
                        }
                    }
                }
                if(hasequivalent){
                    foundgroups=true;
                    StringBuilder group=new StringBuilder("{S"+i);
                    processed[i]=true;
                    for(int j=i+1;j<states_num;j++){
                        if(!table[j][i].iscrossed){
                            group.append(", S").append(j);
                            processed[j]=true;
                        }
                    }
                    group.append("}");
                    System.out.println(group.toString());
                }
                else{
                    processed[i]=true;
                }
            }
        }
         if(!foundgroups)
             System.out.println("No equivalent states found");
         new implication_gui(states_num,table);

    }

}
