import javax.swing.*;
import java.awt.*;

public class implication_gui extends JFrame {
    private int states_num;
    private cell[][] table;

    public implication_gui(int states_num, cell[][] table) {
        this.states_num = states_num;
        this.table = table;
        setTitle("State Minimization Implication Table");
        setSize(600, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        TablePanel panel = new TablePanel();
        add(panel, BorderLayout.CENTER);
        setVisible(true);
    }
    class TablePanel extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int cellSize = 60;
            int margin = 60;
            for (int i = 1; i < states_num; i++) {
                for (int j = 0; j < i; j++) {
                    int x = margin + (j * cellSize);
                    int y = margin + (i * cellSize);
                    g.setColor(Color.BLACK);
                    g.drawRect(x, y, cellSize, cellSize);
                    if (table[i][j].iscrossed) {
                        g.setColor(Color.RED);
                        g.drawLine(x + 5, y + 5, x + cellSize - 5, y + cellSize - 5);
                        g.drawLine(x + cellSize - 5, y + 5, x + 5, y + cellSize - 5);
                    } else {
                        g.setColor(new Color(0, 150, 0));
                        g.drawString("EQUIV", x + 10, y + (cellSize / 2));
                    }
                    g.setColor(Color.BLACK);
                    g.drawString("S" + i, margin - 40, y + (cellSize / 2));
                    g.drawString("S" + j, x + (cellSize / 2), margin - 20);
                }
            }
        }
    }
}