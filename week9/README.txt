From Google Colab GBU T4 used.

test run Grover’s search with PyTorch on both the GPU and the CPU:
1111111111111101
With GPU: 2.0311537900000003 s
1111111111111101
With CPU (single-core): 20.433527507 s

Appendix A: A Complete Implementation
simulator of 40 lines of code and Grover’s search of 23 lines.
[0.48449707 0.51550293]
[0.45445636 0.54554364]
[0.41174808 0.58825192]
[0.35903106 0.64096894]
[0.29958726 0.70041274]
[0.2371174 0.7628826]
[0.17551059 0.82448941]
[0.11860222 0.88139778]
[0.06993516 0.93006484]
[0.03253923 0.96746077]
[0.00874254 0.99125746]
[2.65827874e-05 9.99973417e-01]
11111101

Appendix B: A Minimalist Quantum Computer
A complete implementation in just twelve lines, just to show it’s possible! Grover’s search here is 30 lines.
1111111101