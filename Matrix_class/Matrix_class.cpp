///BenYamin Salimi | Cyangen.ir | BenYamin.Salimi@Gmail.Com
#include <iostream>
using namespace std;

class Matrix
{
	friend ostream &operator<<(ostream &output,Matrix &Ary);
	friend istream &operator>>(istream &input,Matrix &Ary);
private:
    /// matris 313 tayi dar nazar migirim va ba setoon va radif mohasebat ro mahdood mikonim!
	int matrix[313][313];
	int radif,setoon;
public:
	Matrix(){};
	Matrix(int radif,int setoon)
	{
	    Matrix::radif=radif;
        Matrix::setoon=setoon;
        for (int i=0;i<radif;i++)
		for (int j=0;j<setoon;j++)
			Matrix::matrix[i][j]=0;
	}
	Matrix operator+(Matrix d);
	Matrix operator*(Matrix k);
	bool operator==(Matrix u);
	bool operator!=(Matrix o);
};


Matrix Matrix::operator+(Matrix d)
{
	Matrix c(d.radif,d.setoon);
	for (int i=0;i<radif;i++)
		for (int j=0;j<setoon;j++)
			c.matrix[i][j]=Matrix::matrix[i][j]+d.matrix[i][j];
	return c;
}
Matrix Matrix::operator*(Matrix k)
{
	if (Matrix::setoon==k.radif)
	{
		int counter;
		Matrix javab(Matrix::radif,k.setoon);
		for (int i=0;i<radif;i++)
		{
			counter=0;
			while (counter!=k.setoon)
			{
				for (int j=0;j<setoon;j++)
					javab.matrix[i][counter]+=Matrix::matrix[i][j]*k.matrix[j][counter];
				counter++;
			}
		}
		return javab;
	}
	else
		cout<<"in matrix ha nmitavanan dar ham zar zarb shavand";
}
bool Matrix::operator==(Matrix u)
{
	for (int i=0;i<radif;i++)
		for (int j=0;j<setoon;j++)
			if (Matrix::matrix[i][j]!=u.matrix[i][j])
				return false;
	return true;
}
bool Matrix::operator!=(Matrix o)
{
	for (int i=0;i<radif;i++)
		for (int j=0;j<setoon;j++)
			if (Matrix::matrix[i][j]!=o.matrix[i][j])
				return true;
	return false;
}
ostream &operator<<(ostream &output,Matrix &Ary)
{
	for (int i=0;i<Ary.radif;i++)
	{
		for (int j=0;j<Ary.setoon;j++)
			output<<Ary.matrix[i][j]<<",";
		output<<"\b \n";
	}
	return output;
}
istream &operator>>(istream &input,Matrix &Ary)
{
	for (int i=0;i<Ary.radif;i++)
		for (int j=0;j<Ary.setoon;j++)
			input>>Ary.matrix[i][j];
	return input;
}
/// Wish u the best 
