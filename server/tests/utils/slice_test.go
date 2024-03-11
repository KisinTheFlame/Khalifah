package utils_test

import (
	"fmt"
	"testing"

	"github.com/KisinTheFlame/khalifah/server/utils/slice"
)

func TestEqual(t *testing.T) {
	if !slice.Equal([]int{1, 2, 3}, []int{1, 2, 3}) {
		t.Fail()
	}
	if !slice.Equal([]int{}, []int{}) {
		t.Fail()
	}
	if !slice.Equal[int](nil, nil) {
		t.Fail()
	}
	if slice.Equal([]int{1, 2, 3}, []int{1, 2, 4}) {
		t.Fail()
	}
	if slice.Equal([]int{1, 2, 3}, []int{1, 2}) {
		t.Fail()
	}
	if slice.Equal([]int{1, 2, 3}, nil) {
		t.Fail()
	}
	if slice.Equal([]int{}, nil) {
		t.Fail()
	}
}

func TestMap(t *testing.T) {
	s := slice.Map([]int{1, 2, 3}, func(x int) string { return fmt.Sprint(x) })
	if !slice.Equal(s, []string{"1", "2", "3"}) {
		t.Fail()
	}
}
