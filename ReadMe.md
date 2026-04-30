# Первая часть 
![Alt текст](Discription/1_task/AlwaysZero.png)
![Alt текст](Discription/1_task/LineLen.png)
![Alt текст](Discription/1_task/FirstSym.png)
![Alt текст](Discription/1_task/SymSum.png)
![Alt текст](Discription/1_task/SymSum_4001.png)
![Alt текст](Discription/1_task/ROL.png)
![Alt текст](Discription/1_task/ROR.png)
![Alt текст](Discription/1_task/ROR_GodBolt.png)
![Alt текст](Discription/1_task/DJB2.png)
![Alt текст](Discription/1_task/CRC_32.png)
![Alt текст](Discription/1_task/Disp.png)
# Вторая часть
![Alt текст](Discription/2_task/PERF_zero_optimization.png)
![Alt текст](Discription/2_task/PERF_after_CRC_32_opt.png)
![Alt текст](Discription/2_task/PERF_with_MyStrCmp.png)
![Alt текст](Discription/2_task/PERF_MyStrCmp_Problem.png)
![Alt текст](Discription/2_task/PERF_MyStrCmp_after_opt.png)
![Alt текст](Discription/2_task/PERF_IsWord_PROBLEM.png)
![Alt текст](Discription/2_task/PERF_ISWOrd_PROBLEM_2.png)
![Alt текст](Discription/2_task/PERF_DIV_Problem.png)
![Alt текст](Discription/2_task/PERF_Prefetch_Problem.png)

# Анализ ускорения оптимизаций

## Исходные данные

| Оптимизация | Время (с) | Ускорение (к предыдущему) | Количество тиков | Относительная погрешность |
|-------------|-----------|---------------------------|------------------|----------------------------|
| Никакой | 23.31 | — | 98.3139914702222e10 | 3.34% |
| `-O3` | 5.86 | 74.85% | 2.58926614268e10 | 4.95% |
| Интринсик в `CRC_32` | 3.43 | 41.52% | 1.49307318872e10 | 4.18% |
| `MyStrCmp` | 2.61 | 23.77% | 1.196117057197e10 | 3.31% |
| Оптимизировал `MyStrCmp` + `IsWordInList` | 2.48 | 5.04% | 1.12432056358e10 | 1.01% |
| Prefetch | 2.42 | 2.51% | 1.02057337988e10 | 0.83% |
| Div → MulX | 2.38 | 1.63% | 1.01882392774e10 | 0.93% |

## Итоговое ускорение

- **Относительное снижение времени:**  
  (23,31 − 2,38) / 23,31 × 100% ≈ 89,79%

- **Во сколько раз быстрее:**  
  23,31 / 2,38 ≈ 9,79

- **На сколько процентов быстрее:**  
  (23,31 / 2,38 − 1) × 100% ≈ 879%
