func magic1
formal 4
formal 4
localloc 4
bgnstmt 17
label L1
t1 := param 0
t2 := @i t1
t3 := param 1
t4 := @i t3
t5 := t2 <i t4
bt t5 B1
br B2
label L2
t6 := param 0
t7 := 1
t8 := @i t6
t9 := t8 +i t7
t10 := t6 =i t9
br B3
label L3
bgnstmt 18
t11 := local 0
t12 := 0
t13 := t11 =i t12
bgnstmt 19
label L4
bgnstmt 20
t14 := local 0
t15 := 1
t16 := @i t14
t17 := t16 +i t15
t18 := t14 =i t17
bgnstmt 21
t19 := global magic2
t20 := fi t19 0
label L5
t21 := local 0
t22 := @i t21
t23 := param 1
t24 := @i t23
t25 := t22 <i t24
bt t25 B4
br B5
label L6
B4=L4
B5=L6
br B6
label L7
B1=L3
B2=L7
B3=L1
B6=L2
bgnstmt 26
t26 := local 0
t27 := @i t26
t28 := param 0
t29 := @i t28
t30 := t27 *i t29
t31 := param 1
t32 := @i t31
t33 := t30 *i t32
reti t33
fend
func magic2
formal 8
formal 8
localloc 4
localloc 4
localloc 4
localloc 4
localloc 4
bgnstmt 31
t34 := local 0
t35 := param 0
t36 := @f t35
t37 := cvi t36
t38 := t34 =i t37
bgnstmt 32
t39 := local 1
t40 := param 0
t41 := @f t40
t42 := param 1
t43 := @f t42
t44 := t41 *f t43
t45 := cvi t44
t46 := t39 =i t45
bgnstmt 33
t47 := local 2
t48 := local 0
t49 := @i t48
t50 := local 1
t51 := @i t50
t52 := t49 *i t51
t53 := t47 =i t52
bgnstmt 34
t54 := local 3
t55 := local 2
t56 := @i t55
t57 := t54 =i t56
bgnstmt 36
label L8
bgnstmt 37
t58 := local 0
t59 := 1
t60 := @i t58
t61 := t60 +i t59
t62 := t58 =i t61
bgnstmt 38
label L9
t63 := local 2
t64 := @i t63
t65 := 0
t66 := t64 !=i t65
bt t66 B7
br B8
label L10
bgnstmt 39
t67 := local 2
t68 := 1
t69 := @i t67
t70 := t69 -i t68
t71 := t67 =i t70
br B9
label L11
B7=L10
B8=L11
B9=L9
bgnstmt 41
t72 := "%d\n"
t73 := local 3
t74 := @i t73
t75 := local 2
t76 := @i t75
t77 := t74 -i t76
argi t72
argi t77
t78 := global printf
t79 := fi t78 2
bgnstmt 42
t80 := local 3
t81 := 1
t82 := @i t80
t83 := t82 -i t81
t84 := t80 =i t83
bgnstmt 43
t85 := local 2
t86 := local 3
t87 := @i t86
t88 := t85 =i t87
bgnstmt 44
t89 := local 4
t90 := 1
t91 := @i t89
t92 := t91 +i t90
t93 := t89 =i t92
label L12
t94 := local 1
t95 := @i t94
t96 := local 0
t97 := @i t96
t98 := t95 >i t97
bt t98 B10
br B11
label L13
B10=L8
B11=L13
bgnstmt 48
t99 := local 0
t100 := @i t99
t101 := local 4
t102 := @i t101
t103 := t100 *i t102
reti t103
fend
func main
localloc 4
localloc 4
localloc 4
localloc 8
bgnstmt 54
t104 := local 0
t105 := 0
t106 := t104 =i t105
bgnstmt 55
t107 := local 1
t108 := 10
t109 := t107 =i t108
bgnstmt 56
t110 := local 3
t111 := 0
t112 := cvf t111
t113 := t110 =f t112
bgnstmt 58
t114 := local 0
t115 := 0
t116 := t114 =i t115
label L14
t117 := local 0
t118 := @i t117
t119 := local 1
t120 := @i t119
t121 := t118 <i t120
bt t121 B12
br B13
label L15
t122 := local 0
t123 := 1
t124 := @i t122
t125 := t124 +i t123
t126 := t122 =i t125
br B14
label L16
bgnstmt 59
t127 := local 0
t128 := @i t127
t129 := local 1
t130 := @i t129
argi t128
argi t130
t131 := global magic1
t132 := fi t131 2
bgnstmt 60
t133 := global magic2
t134 := fi t133 0
br B15
label L17
B12=L16
B13=L17
B14=L14
B15=L15
bgnstmt 64
t135 := local 0
t136 := 0
t137 := t135 =i t136
label L18
t138 := local 0
t139 := @i t138
t140 := local 1
t141 := @i t140
t142 := t139 <i t141
bt t142 B16
br B17
label L19
t143 := local 0
t144 := 1
t145 := @i t143
t146 := t145 +i t144
t147 := t143 =i t146
br B18
label L20
bgnstmt 65
t148 := local 3
t149 := local 0
t150 := @i t149
t151 := local 1
t152 := @i t151
argi t150
argi t152
t153 := global magic2
t154 := fi t153 2
t155 := local 1
t156 := @i t155
t157 := local 0
t158 := @i t157
argi t156
argi t158
t159 := global magic2
t160 := fi t159 2
argi t154
argi t160
t161 := global magic1
t162 := fi t161 2
t163 := cvf t162
t164 := @f t148
t165 := t164 +f t163
t166 := t148 =f t165
bgnstmt 66
t167 := local 3
t168 := local 1
t169 := @i t168
t170 := local 0
t171 := @i t170
argi t169
argi t171
t172 := global magic2
t173 := fi t172 2
t174 := local 0
t175 := @i t174
t176 := local 1
t177 := @i t176
argi t175
argi t177
t178 := global magic2
t179 := fi t178 2
argi t173
argi t179
t180 := global magic1
t181 := fi t180 2
t182 := cvf t181
t183 := @f t167
t184 := t183 +f t182
t185 := t167 =f t184
bgnstmt 67
t186 := local 3
t187 := local 0
t188 := @i t187
t189 := local 0
t190 := @i t189
argi t188
argi t190
t191 := global magic2
t192 := fi t191 2
t193 := local 1
t194 := @i t193
t195 := local 1
t196 := @i t195
argi t194
argi t196
t197 := global magic2
t198 := fi t197 2
argi t192
argi t198
t199 := global magic1
t200 := fi t199 2
t201 := cvf t200
t202 := @f t186
t203 := t202 *f t201
t204 := t186 =f t203
bgnstmt 68
t205 := local 3
t206 := local 1
t207 := @i t206
t208 := local 1
t209 := @i t208
argi t207
argi t209
t210 := global magic2
t211 := fi t210 2
t212 := local 0
t213 := @i t212
t214 := local 0
t215 := @i t214
argi t213
argi t215
t216 := global magic2
t217 := fi t216 2
argi t211
argi t217
t218 := global magic1
t219 := fi t218 2
t220 := cvf t219
t221 := @f t205
t222 := t221 /f t220
t223 := t205 =f t222
br B19
label L21
B16=L20
B17=L21
B18=L18
B19=L19
bgnstmt 72
t224 := "l is %d\n"
t225 := local 3
t226 := @f t225
argi t224
argf t226
t227 := global printf
t228 := fi t227 2
fend
