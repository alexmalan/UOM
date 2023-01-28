import java.util.ArrayList;
import java.util.Random;

public class Server
{
  public static void main(String[] args)
  {
    int req_counter = 0;
    int req = 0;
    int simulation = 1000000;
    int fin_req = 0;
    int den_req = 0;
    double avg_q_size = 0;
    double avg_rasp = 0;

    int q_size = Integer.parseInt(args[0]);
    int arrivals = Integer.parseInt(args[1]);
    int no_of_servers = Integer.parseInt(args[2]);
    int time_needed = Integer.parseInt(args[3]);

    int[][] running_servers = new int[2][no_of_servers];

    int time_slice = 1;

    ArrayList<Integer> q_of_req = new ArrayList<Integer>();
    while(time_slice <= simulation)
    {
      avg_q_size = avg_q_size + (double)q_of_req.size()/simulation;

      Random nr = new Random();
      double prob = nr.nextDouble();

      if(prob < 1/(double)arrivals)
      {
        req_counter++;
        if(q_of_req.size()<=q_size)
          q_of_req.add(time_slice);
        else
          den_req++;
      }

      for(int index = 0; index< no_of_servers; index++)
      {
        if(running_servers[0][index]-1==0)
        {
          int rasp = time_slice- running_servers[1][index];
          avg_rasp = avg_rasp + rasp;
          fin_req++;
        }
        if(running_servers[0][index] > 0)
          running_servers[0][index]--;

        if(running_servers[0][index]==0)
          running_servers[0][index] = 0;
      }
      int i = 0;
      while(i<no_of_servers)
      {
        if(q_of_req.size() > 0)
        {
          if(running_servers[0][i]==0)
          {
            running_servers[0][i] = time_needed;
            running_servers[1][i] = q_of_req.get(0);
            q_of_req.remove(0);
          }
        }
        i++;
      }
      time_slice++;
    }
    avg_rasp = avg_rasp /fin_req;
    for(int index = 0; index < no_of_servers; index++)
      if(running_servers[0][index] > 0)
        req++;

    double percentage = ((double)den_req / (double)req_counter*100);


    System.out.println("Total requests: " + req_counter);
    System.out.println("Rejected: " + den_req);
    System.out.println("Percentage of rejected requests: " + percentage);
    System.out.println("Average queue size: " + avg_q_size);
    System.out.println("Average response time: "+ avg_rasp);
    System.out.println("Requests cmpleted at the end of simulation:" + fin_req);
    System.out.println("Requests running at the end of simulation: " + req);
    System.out.println("queue length at the end of simulation: " + q_of_req.size());

  }
}