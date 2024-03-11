package slice

import "cmp"

func Equal[E cmp.Ordered](s []E, t []E) bool {
	if s == nil || t == nil {
		return s == nil && t == nil
	}
	if len(s) != len(t) {
		return false
	}
	for i, e := range s {
		if e != t[i] {
			return false
		}
	}
	return true
}

func Map[T ~[]E, E any, S any](slice T, mappingFunc func(E) S) []S {
	newSlice := make([]S, len(slice))
	for i, t := range slice {
		newSlice[i] = mappingFunc(t)
	}
	return newSlice
}
