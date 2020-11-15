//≤ªŒ»∂®≈≈–Ú
QuickSort(int* a, int start, int end)
{
	if (start < end)
	{
		
		int i = start;
		int j = end;
		int t = a[start];
		while (i < j)
		{
			while (i < j && t <= a[j])
				j--;
			if (i < j)a[i] = a[j];
			while (i < j && t >= a[i])
				i++;
			if (i < j)a[j] = a[i];
		}
		a[i] = t;
		QuickSort(a,  start, i - 1);
		QuickSort(a, i + 1, end);
	}
}