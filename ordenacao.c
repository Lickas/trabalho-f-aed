void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void quick_sort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int p = particionamento(arr, baixo, alto); 
        quick_sort(arr, baixo, p - 1);
        quick_sort(arr, p + 1, alto);
    }
}