#ifndef NEURON
#define NEURON
class Neuron
{
public:
    double mul [25][25];
    double weight [25][25];
    double input [25][25] ;
    int limit;
    double sum;
    Neuron(){
        sum = 0;
        limit = 1000;
    }

    void mul_w()
    {
        for (int x = 0; x < 25; x++)
         {
            for (int y = 0; y < 25; y++)
                {
                   mul[x][y] = input[x][y]*weight[x][y];
                }
         }
     }
    void Sum()
             {
                 sum = 0;
                 for (int x = 0; x < 25; x++)
                 {
                     for (int y = 0; y < 25; y++)
                     {
                         sum += mul[x][y];
                     }
                 }
             }
    bool Rez()
        {
           if (sum >= limit)
               return true;
            else return false;
         }

};

#endif // NEURON




