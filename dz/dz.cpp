#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ukr");

	const int N = 100;
	double arr[N];

	for (int i = 0; i < N; i++) {
		arr[i] = sin(5 * i * M_PI / 180);
	}

	int index = -1;
	double sum = 0.0;
	double three = 3.0;

	__asm {
		finit					// Ініціалізуємо FPU
        fldz					// Завантажуємо 0 у FPU
        xor ECX, ECX			// Ініціалізацуємо лічильник циклу ECX = 0
	m1: finit					// Зкидуємо все до параметрів по замовчуваню
		fld sum					// Завантажуємо sum у стек FPU
		fld arr[ECX*8]			// Завантажити arr[ECX] у стек FPU
        faddp st(1), st(0)		// Додати arr[ECX] до поточної суми (sum += arr[ECX])
        fstp sum				// Зберегти поточну суму у змінну sum
		fld three				// Завантажуємо 3 у стек FPU
		fld sum					// Завантажуємо поточну суму у FPU
        fcomip st(0), st(1)		// Порівнюємо поточну суму з 3 (st(0) - sum, st(1) - 3)
		jnb m2					// Якщо сума >= 3, переходимо до m2
        inc ECX					// Збільшуємо лічильник
        cmp ECX, N				// Перевіряємо, чи не досягнуто кінця масиву
        jl m1					// Якщо ні, повторюємо цикл
        mov ECX, -1				// Якщо кінець масиву досягнутий, встановлюємо ECX в -1
    m2: mov index, ECX			// Зберігаємо поточне значення ECX в index
	}
	cout << "Сума елеменiв що перевищiть 3 при iндексi: " << index << endl;
}
