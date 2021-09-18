# ParallelMatrixProduct
Paralle Matrix Realization for huawei scholaship programm

Программа 2 основных метода  ProductMX(double** a, double** b, int row1, int row2, int col1, int col2)
и ParallelProductMX(double** a, double** b, int row1, int row2, int col1, int col2), которые реализуют перемножение матриц a и b размерами row1*col1 и row2*col2
линейным и параллельным образом.

Для распараллеливания вычислений была выбрана технология OpenMP, в первую очередь из-за простоты освоения.

На вход программа принимает 4 целых числа row1, col1, row2, col2 размеры двух перемножаемых матриц.
Программа сама заполняет матрицы указанного размера и вычисляет их произведение двумя методами, сравнивая затраченное время.
