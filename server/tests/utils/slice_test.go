package utils_test

import (
	"fmt"
	"testing"

	"github.com/KisinTheFlame/khalifah/server/utils/sliceutils"
)

func TestEqual(t *testing.T) {
	if !sliceutils.Equal([]int{1, 2, 3}, []int{1, 2, 3}) {
		t.Fail()
	}
	if !sliceutils.Equal([]int{}, []int{}) {
		t.Fail()
	}
	if !sliceutils.Equal[int](nil, nil) {
		t.Fail()
	}
	if sliceutils.Equal([]int{1, 2, 3}, []int{1, 2, 4}) {
		t.Fail()
	}
	if sliceutils.Equal([]int{1, 2, 3}, []int{1, 2}) {
		t.Fail()
	}
	if sliceutils.Equal([]int{1, 2, 3}, nil) {
		t.Fail()
	}
	if sliceutils.Equal([]int{}, nil) {
		t.Fail()
	}
}

func TestMap(t *testing.T) {
	s := sliceutils.Map([]int{1, 2, 3}, func(x int) string { return fmt.Sprint(x) })
	if !sliceutils.Equal(s, []string{"1", "2", "3"}) {
		t.Fail()
	}
}
