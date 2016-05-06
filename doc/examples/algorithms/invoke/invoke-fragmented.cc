/*
 * Copyright (c) 2014-2016, Siemens AG. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <embb/algorithms/algorithms.h>
#include <cassert>

#include "algorithms/invoke/packages-snippet.h"

static int a = 0, b = 0, c = 0;

void WorkPackageA() {
  a++;
}

void WorkPackageB() {
  b++;
}

void WorkPackageC() {
  c++;
}

int* Partition(int* first, int* last) {
  int* pivot = last - 1;
  while (first != last) {
    while (*first < *pivot) {
      ++first;
      if (first == last) return first;
    }
    do {
      --last;
      if (first == last) return first;
    } while (*pivot < *last);
    std::swap(*first, *last);
    if(pivot == first) {
      pivot = last;
    } else if (pivot == last) {
      pivot = first;
    }
    ++first;
  }
  return first;
}

#include "algorithms/invoke/quick_sort-snippet.h"

#include "algorithms/invoke/parallel_quick_sort-snippet.h"

/**
 * Example using embb::algorithms::ParallelInvoke() to execute work packages in
 * parallel.
 */
void RunInvoke() {
  #include "algorithms/invoke/invocation-snippet.h"
  assert(a == 1);
  assert(b == 1);
  assert(c == 1);

  {
    int range[] = {2, 5, 3, 1, 4};
    QuickSort(range, range + 5);
    for (size_t i = 0; i < 5; i++) {
      assert(range[i] == static_cast<int>(i) + 1);
    }
  }
  {
    int range[] = {2, 5, 3, 1, 4};
    ParallelQuickSort(range, range + 5);
    for (size_t i = 0; i < 5; i++) {
      assert(range[i] == static_cast<int>(i) + 1);
    }
  }
}



