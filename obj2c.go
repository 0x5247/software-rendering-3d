package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// ref: https://github.com/tsoding/formula/issues/2
func main() {
	objFpath := ""
	if len(os.Args) >= 2 {
		objFpath = os.Args[1]
	} else {
		fmt.Fprintln(os.Stderr, "gimme file name")
		return
	}

	objFile, err := os.Open(objFpath)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		return
	}
	defer objFile.Close()

	vs := make([][3]float32, 0, 32)
	fs := make([][]uint16, 0, 32)
	fsLen := uint(1)

	scanner := bufio.NewScanner(objFile)
	lineNo := uint(0)

	for scanner.Scan() {
		lineNo += 1

		line := strings.TrimSpace(scanner.Text())

		if strings.HasPrefix(line, "f ") {
			f := make([]uint16, 0)
			for part := range strings.SplitSeq(line[2:], " ") {
				if len(part) == 0 {
					continue
				}

				delimIdx := strings.Index(part, "/")
				if delimIdx == -1 {
					fmt.Fprintln(os.Stderr, "error: malformed data at line number ", lineNo)
					return
				}

				n, err := strconv.ParseInt(part[0:delimIdx], 10, 16)
				if err != nil {
					fmt.Fprintln(os.Stderr, "error: malformed data at line number ", lineNo)
					fmt.Fprintln(os.Stderr, err)
				}

				f = append(f, uint16(n - 1))
			}
			fs = append(fs, f)
			fsLen += uint(len(f)) + 1
		} else if strings.HasPrefix(line, "v ") {
			v := [3]float32{}
			idx := uint(0)

			for part := range strings.SplitSeq(line[2:], " ") {
				if len(part) == 0 {
					continue
				}

				n, err := strconv.ParseFloat(part, 32)
				if err != nil {
					fmt.Fprintln(os.Stderr, "error: malformed data at line number ", lineNo)
					fmt.Fprintln(os.Stderr, err)
					return
				}

				if idx >= uint(len(v)) {
					fmt.Fprintln(os.Stderr, "error: malformed data at line number ", lineNo)
					fmt.Fprintln(os.Stderr, "too many dimentions")
					return
				}

				v[idx] = float32(n)

				idx += 1
			}

			vs = append(vs, v)
		}
	}

	// centering it
	min := math.Inf(10)
	max := math.Inf(-1)

	minX := min
	minY := min
	minZ := min
	maxX := max
	maxY := max
	maxZ := max

	for _, v := range vs {
		minX = math.Min(minX, float64(v[0]));
		maxX = math.Max(maxX, float64(v[0]));
		minY = math.Min(minY, float64(v[1]));
		maxY = math.Max(maxY, float64(v[1]));
		minZ = math.Min(minZ, float64(v[2]));
		maxZ = math.Max(maxZ, float64(v[2]));
	}

	c := [3]float32{
		float32((minX + maxX) / 2),
		float32((minY + maxY) / 2),
		float32((minZ + maxZ) / 2),
	}

	for i := range vs {
		vs[i][0] -= c[0]
		vs[i][1] -= c[1]
		vs[i][2] -= c[2]
	}

	fmt.Println("#include \"base.h\"\n")

	fmt.Println("// generated with obj2c.go\n")

	fmt.Printf("#define FS_LEN %v\n\n", len(fs))

	fmt.Printf("const vec3f vs[%v] = {\n", len(vs))
	for _, v := range vs {
		fmt.Printf("\t{%v,%v,%v},\n", v[0], v[1], v[2])
	}
	fmt.Println("};\n")

	fmt.Printf("const uint16_t fs[%v] = {\n", fsLen)
	for _, f := range fs {
		fmt.Printf("\t%v,", len(f))

		for _, n := range f {
			fmt.Printf("%v,", n)
		}

		fmt.Println()
	}
	fmt.Println("\t0\n};")

	fmt.Fprintf(os.Stderr, "vs.len: %v, fs.len: %v, fss.len: %v\n", len(vs), len(fs), fsLen)
}
