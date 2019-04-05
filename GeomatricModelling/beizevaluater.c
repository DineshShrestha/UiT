#include"beizevaluater.h"

template <typename T>
BeizEvaluater<T>::BeizEvaluater()
{

}

template<typename T>
void BeizEvaluater<T>::BeizerEvaluater(GMlib::DMatrix<T> &B, int d, T scale, T t)
{
    //scale =1;
    if(d<1){

        B.setDim(1,1);
        B[0][0]=1;
        return;  //escape in the case of degree zero
    }
    else
        B.setDim(d+1, d+1);//initiate the result matrix
        //compute all Bernstein polynomials up to degree d
        //each degree at each row, starting from the bottom up
        B[d-1][0]=1-t;
        B[d-1][1]=t;

        for(int i=d-2;i>=0;i--){
            B[i][0]=(1-t)*B[i+1][0];
            for (int j=1;j<d-i;j++)
            {
                B[i][j]=t*B[i+1][j-1] + (1-t)*B[i+1][j];
            }
            B[i][d-i]=t*B[i+1][d-i-1];
        }
//        for(int i=0;i<B.getDim2();i++)
//            std::cout<<"matrix B["<<i<<"]="<<B[0][i]<<std::endl;

        //compute all the derivatives that exist
        B[d][0] = -scale;
        B[d][1] =scale;

        for(int k=2;k<=d;k++){
            const double s= k*scale;
            for(int i=d;i>d-k;i--){
                B[i][k] = s*B[i][k-1];
                for(int j=k-1;j>0;j--)
                {
                    B[i][j]= s* (B[i][j-1]-B[i][j]);
                }
                B[i][0] = -s*B[i][0];
            }

        }
        //std::cout<<"b matrix is:"<<B<<std::endl;
}
template <typename T>
void BeizEvaluater<T>::BSplineEvaluater(GMlib::DMatrix<T>&B, std::shared_ptr<knotVector<T>> kv, int d, T tp)
{

    _knotVector =kv;
  int index=d;
  //std::cout<<"index="<3<index<<"center point="<<tp<<"\nknotvector="<<*_knotVector<<std::endl;
    if(tp>_knotVector->getParam(index+1))
    {
        index++;
    }

      B.setDim( d+1, d+1 );
      GMlib::DVector<T> w(d);

      // Compute the Bernstein-Hermite polynomials 1 -> d.
      // One for each row, starting from the bottom up.

      w[0] = W(tp,1,index);
      B[d-1][0] = 1 - w[0];
      B[d-1][1] = W(tp,d,index);
      for( int i = d-2, dc=2; i >= 0; i--, dc++ )
      {
          //generate w
          w.setDim(dc);
        for( int j = dc; j >0; j-- )
        {
            w[j-1] = W(tp,dc,index-(dc-j));
        }
            //compute bernstein polynomials
        B[i][0] = ( 1 - w[0]) * B[index+1][0];
        for( int k = 1; k < d-index; k++ )
          {
            B[i][k] = w[k-1] * B[i+1][k-1] + (1 - w[k]) * B[i+1][k];
          }
            B[i][d-i] = w[dc-1]* B[i+1][d-i-1];
      }
      // Compute all the deriatives :P
       //w[0] = delta(scale,1,ii);
     // w[0] = Wder(tp,1,index);
      B[d][0] =- Wder(tp,1,index);//-w[0];
      B[d][1] =  Wder(tp,1,index);//w[0];

      for( int k = 2; k <= d; k++ )
      {
        //const double s = k * scale;
        for( int i = d, dc=2; i > d - k; i--, dc++ )
        {

            w.setDim(dc);
          for( int j = 1; j <=dc; j++ )
          {
              w[j-1] = k*Wder(tp,dc,index-(dc-j));//change from j to k

            }
              //complete the bernstein polynomial by adding the computation of derivatives
          B[i][k] = w[0] * B[i][k-1];
          for( int j = k - 1 ,index_c=1; j > 0; j--, index_c++ )
            {
              B[i][j] = w[index_c] *( B[i][j-1] - B[i][j]) ;
             }
              B[i][0] = - w[dc-1]* B[i][0];
        }
      }
      std::cout<<"matrix:\n"<<B<<std::endl;
}

template <typename T>
T BeizEvaluater<T>::W(T tp, int d, int i)
{
    return(tp- _knotVector->getParam(i))/(_knotVector->getParam(i+d)-_knotVector->getParam(i));
  }

template <typename T>
T BeizEvaluater<T>:: Wder(T tp, int d, int i)
{
    return T(1) / ( _knotVector->getParam(i+d) - _knotVector->getParam(i) );
}


