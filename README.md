
# ⚡ Optimized Multi-Threaded Merge Sort in C++

This project implements an optimized version of Merge Sort in C++ using both manual multithreading (`std::thread`) and asynchronous futures (`std::async`). The goal is to compare the performance of:

- 🔹 Standard C++ STL `std::sort()`
- 🔹 Normal recursive Merge Sort
- 🔹 Manually threaded Merge Sort
- 🔹 Future-based threaded Merge Sort

## 🚀 Motivation

Merge Sort is a divide-and-conquer algorithm and a great candidate for parallelization. As datasets grow larger, the bottleneck shifts from algorithmic complexity to CPU utilization. This project explores **parallelizing merge sort** to better utilize **multi-core CPUs**.

---

## 🧵 Multithreading Approaches

### 1. 🛠️ Normal Merge Sort
Classic recursive merge sort without any parallelization. All work is done on a single thread.

### 2. ⚙️ Threaded Merge Sort (`std::thread`)
This version uses `std::thread` to parallelize the two halves of the recursive sort — but only up to a certain **recursion depth** to avoid thread explosion.

```cpp
if (depth <= 3) {
    std::thread left_thread(...);
    std::thread right_thread(...);
    left_thread.join();
    right_thread.join();
}
```

### 3. 🔮 Future-based Merge Sort (`std::async`)
This variant uses `std::async` for potentially better thread pool management and task scheduling handled by the runtime.

```cpp
if (depth <= 3) {
    auto leftFuther = std::async(...);
    auto rightFuther = std::async(...);
    leftFuther.get();
    rightFuther.get();
}
```

---

## 📈 Optimization Strategy

- **Controlled parallelism**: Threads are spawned only up to a certain recursion depth to reduce overhead.
- **Zero-copy merging**: Efficient merge logic minimizes memory overhead.
- **Multiple containers**: The original vector is cloned for a fair time comparison between algorithms.

---

## 📊 Performance Comparison

All times are measured in **seconds** on the same hardware and under identical conditions.

| Elements | `std::sort()` | Normal Merge Sort | Threaded Merge Sort | Future Threaded Merge Sort |
|----------|---------------|-------------------|----------------------|-----------------------------|
| 1        | 5.1e-06       | 2.0e-07           | 1.0e-07              | 1.0e-07                     |
| 10       | 2.9e-06       | 1.18e-05          | 0.0034324            | 0.0010545                   |
| 100      | 1.09e-05      | 8.69e-05          | 0.0030243            | 0.0015799                   |
| 1,000    | 9.44e-05      | 0.0009584         | 0.0034466            | 0.0031919                   |
| 10,000   | 0.0008487     | 0.0166312         | 0.0097118            | 0.01144                     |
| 10,000   | 0.0010888     | 0.0076391         | 0.0221145            | 0.0052548                   |
| 100,000  | 0.0094151     | 0.0773687         | 0.0437115            | 0.0391605                   |
| 1,000,000| 0.102327      | 0.776259          | 0.314771             | 0.343081                    |
| 10,000,000| 1.23652      | 9.35154           | 3.28113              | 3.38501                     |
| 100,000,000| 13.3938     | 102.46            | 52.122               | 69.0183                     |

---
![WhatsApp Image 2025-06-15 at 00 43 21_ce481aed](https://github.com/user-attachments/assets/62e37431-a2b5-4b4a-aec7-e3212ec9f2d1)


## 👁️ Visual Representation
![merge_sort_performance](https://github.com/user-attachments/assets/5389ff6b-f96f-494f-99bf-9fa63228fc75)


## 🧠 Key Insights

- For **very small datasets**, threading introduces overhead and can actually **slow down** execution.
- For **medium to large datasets**, threaded merge sort drastically outperforms the standard merge sort.
- The **future-based version** is sometimes slightly slower than manual threads — this depends on how `std::async` is implemented (thread pool vs. spawn-on-demand).
- At scale (10M+), both multithreaded versions **cut down execution time by over 50%** compared to the standard implementation.

---

## 🛠️ How to Build & Run

### 🔧 Compile
```bash
g++ -std=c++17 -O2 -pthread mergeOptimized.cpp -o mergeOptimized
```

### 🚀 Run
```bash
./mergeOptimized
```
Then input the number of elements when prompted.

---

## 📦 Possible Improvements

- Introduce a **dynamic thread pool**.
- Use **iterators** to make functions more STL-compatible.
- Experiment with **OpenMP** or **TBB** for more optimized parallelism.
- Benchmark on systems with **different core counts**.

---

## 👨‍💻 Author

Made with ❤️ by Mani, optimized for performance.

---
