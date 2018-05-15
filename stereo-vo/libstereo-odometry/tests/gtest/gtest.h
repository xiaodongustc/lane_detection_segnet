// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the public API for Google Test.  It should be
// included by any test program that uses Google Test.
//
// IMPORTANT NOTE: Due to limitation of the C++ language, we have to
// leave some internal implementation details in this header file.
// They are clearly marked by comments like this:
//
//   // INTERNAL IMPLEMENTATION - DO NOT USE IN A USER PROGRAM.
//
// Such code is NOT meant to be used by a user directly, and is subject
// to CHANGE WITHOUT NOTICE.  Therefore DO NOT DEPEND ON IT in a user
// program!
//
// Acknowledgment: Google Test borrowed the idea of automatic test
// registration from Barthelemy Dagenais' (barthelemy@prologique.com)
// easyUnit framework.

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_H_

#include <limits>
#include <vector>

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file declares functions and macros used internally by
// Google Test.  They are subject to change without notice.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan)
//
// Low-level types and utilities for porting Google Test to various
// platforms.  They are subject to change without notice.  DO NOT USE
// THEM IN USER CODE.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_

// The user can define the following macros in the build script to
// control Google Test's behavior.  If the user doesn't define a macro
// in this list, Google Test will define it.
//
//   GTEST_HAS_CLONE          - Define it to 1/0 to indicate that clone(2)
//                              is/isn't available.
//   GTEST_HAS_EXCEPTIONS     - Define it to 1/0 to indicate that exceptions
//                              are enabled.
//   GTEST_HAS_GLOBAL_STRING  - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::string, which is different to std::string).
//   GTEST_HAS_GLOBAL_WSTRING - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::wstring, which is different to std::wstring).
//   GTEST_HAS_PTHREAD        - Define it to 1/0 to indicate that <pthread.h>
//                              is/isn't available.
//   GTEST_HAS_RTTI           - Define it to 1/0 to indicate that RTTI is/isn't
//                              enabled.
//   GTEST_HAS_STD_WSTRING    - Define it to 1/0 to indicate that
//                              std::wstring does/doesn't work (Google Test can
//                              be used where std::wstring is unavailable).
//   GTEST_HAS_TR1_TUPLE      - Define it to 1/0 to indicate tr1::tuple
//                              is/isn't available.
//   GTEST_HAS_SEH            - Define it to 1/0 to indicate whether the
//                              compiler supports Microsoft's "Structured
//                              Exception Handling".
//   GTEST_USE_OWN_TR1_TUPLE  - Define it to 1/0 to indicate whether Google
//                              Test's own tr1 tuple implementation should be
//                              used.  Unused when the user sets
//               S.�v�z�&/��;�gu���q���9��?$�.�����?(�_��V	��*_v�!�>�=JӦ�1��,�����
�6;�~7.���n���ڜrqr{��w�k�๳Hp��7Ҵ��ׅ
��(�t	�$�����MwB�o�Wp�B��<�=i9���ؠ�q���	�5���YF�6|���|{��T�ut��k���R��OiRb��[ irB�[��z� ��a��c��EAx� ����f6�!�&�p�s�к��\�{�h�������q;��|����L�H����h�z��A|9�����@c�{6��G�l�qMp�ȹӘ�!\�],�Wm� ��`(k���C�%�5���R ���޺�`r�j��+fJ[��HԐ;�������{�:�M���lVq"N�f�pV~X܅*���;ΐ���
{�wF��m��Y�YѮ-%uX}�;\[&u�?�]}TW��B��[��5�Q�Dt[ec+�j�͚h�{�c�ʈ�Buԉd�nV�tz��8���L&;�sf�9�l�	I�Y���1FG4j6մ��I���~TИ9�]�֫��{��}����v�J�����O�?�&���b�?j���z�NQ�Wf�0�wC�"�>I+����K���l�G.�<�v
͂��AOdp:�/����k���6j���f�������Mf�<#�sRe*-� y��Xk���4����=Q�*&i4#��4�i�F��R��R	��m��E���;��j�Tn��ZzA��n;�"�K�a�,A�Jl���W5�?��J;�/J�.9�%�J|G	wP�� �.��v
F����o��%��Ac�]��{��P���]%y�!9	���#��y$g�WJ�M�AN���Я�]���2ϥ>mjM#c�٥�fQ'�Z��F���̋%e���t��Q��$E9�.j�*�����}����U��Ғ�@��gҴ�&�_b�+H�d�9�Ȱ��굏~��0�u~��_�K�|ܩBԬI���٧d�Jݣv�?�_XfT{�؉-�G���zt�������S�/� 1�j�m�l������_�F�����c�J�Ҽ����
�mz��~�_:�.H~�?ɏ;�R�o�z�ˀ����y̗����$yƢ<3d�ٞ'N��9.�K@�����Lf�&��qO[���B��,N�yg&s7 �f�>3=���<��<��#�HSCO���
X�x����s�G&cr>�1K�W�z+a>��ԃ�����?>��L|̭��^�{�#�G�pYV�ubʢ5`ĵ��g�~��
��%$*6�"�#��y*�-���jG�S&��2�,�ɋ�o�Έ�-��\ཕ��Ӌ֌���\��/�@�R��R�b�a�8��� <�#�u�oзW������!��!9A���@�_�o8�e�U6+�S�t��5�5!]���F����Y���IN��_Ep2�L����xV�W����^e��p��2�p^�v�.﷾L�_�ӆ￟����� ��~ٯ���%�������AM��`�K�엹���6�{椐�i3U��T����\c���Bg"��8��D�_W��<��?3���:�p����S�����n��������9��W1�Հ"`\Z��mvx�D�D���Gĵ�6����C�{��]����N+�&�`��M��;�A��;�3.�-10Sx��r��X���N��$�Cʏ�cV��B�q�3B5��j�'�ֱ���F�»=W����{��K���B��<�L}s���բ�0u�kzf�N+I�0M�z�|,ˠ�>OV�x$�����h���>.����>vZO�H��,��F�o�~Ob�����,޵�Ԫ����.�(�6��XS���B�8�{�V�A��k�x{���7�ek��1�rN;C{Y�X>�p�_�
�:�z�#��
[�Q�`�t+�Q����q
e��Z����"]�g�g��%�g14홏ɪ� �w�3��K״y4��\1��&�8�Q������EιTR��U~�}/���I�~"��T�E���t�
�r]�BT���\AW��+WЕ+��t�
�r�D�
Q�U��{)W�)W�҂��ds����l�/w�@�6\Xט������,$��i�`��O=��t޿�LI�oY��؋N�e
�]���U?
�y=[�6r�<bgʤE�q��Δ��۸�z"�2�����ƿ5�"��hFU0oD�R�F��;���.�T��iߟ��S&
N��<#Ceo�*���z�����>��[���R"����i�F�xZl� ��70�rI���W���XL��TJ[F�~8�Q�',����Qԭ��/�=5.�eB�\u�G��H�7�}�
բ=���q~��5���&�9tm��;���^G������G�4�;4��r|�*�y^��u���롱��8H ����P�z'��Ӡ���BMvuS����4�;��[m���1�|fZ��8h�<a0O� rW%�2
�$W���Dm�s�F_9B�qK����~$[?l�$�u�^F9��<�ޙLC܋WF����:.���7�S_�8�
d�~.�i��^��S���w�������`���#I���x�O���L�R@�Өڅ��kOå�kߓ>����g����`���f�d�G�O�	�a!I��:c6��J��qlh^�=/۠yNbo(�3� �|��{o ���qX�P�\���*8���!�n��f'��\5L��V|ǎ���VZ4U+.#�/����<K��q,>p�s��9}(��gcpߘ������9��[I��wŪ>�7��C�B鈛��.g��3��m@1���Ia��_d�G؉�j��R�-�oϦu@�o���|)֜���s����:N�P�q����ɉ��jm��*��RY5��P��UVo0��}���ז�����Sk�K�*w��SﮛQ^S��r�����m����6�<뮫��p6��I�+�{��0O�ͩϕ�kI��2Eʩ�/*⭯���6�
�ֽYz���|S"�.�5��F�]{sUe�"UT���n�P���[m���n��\S�r���AUCe5HRY!�m����NʍSf.=�n������q�J�7�\���_\QRE������
2�W�K��e������g@��ɣczx��|��]/���67�ǺM]�U�Vi���97k�ȶl)�%U��?�e鱥F�T�H�۲�t��Aw1PX�
����n�.�|
xP ����\�.�+����9���<��������+�[���9��9�����Me�5�{�m�[��B͛-�do-_ns�R��U9��˹[$���v�[,gr�Ҵw��ke�)M�k�B�wgM��,�\�����Z��M����
�g�r�V�DsH�W(��9A�N�r)3#��=U(���t�\�sP��e�T�ިʺA_�D�R!�5��j�|M�7��\�o��V�����c���)��;k�{s�T�Qd��2#I�_6Șɲ�T�<�V����wi�.!IN���r�^�ζ�OW��a�4��.�'Qº~�_�Tk�5������i9-��&��?Q��]����Y���(Ǜ��F�GG�V,�kVZ�T�����ˈ	�J��.Nf�'t¤��f���P)�*2�l>��׫���KD�����V� �r�r�0�J[�D��L�����]9�)6��WO�ׁ�x�|h(O'��tb, ����٘���'d���9�YSz
���\��庅m���Z�Z�M�TI��
�B-oM����2�58|u��މ�N*ݨ6H�)���6��������&}��޽)���]�H4
G��I��ņ�QI�GG��@�h0�E�c�d8!V{ >=N�p$�JT�EdRz�Q�jMb },S���	�Y�\�K^o8r�;U�`����JF#�t�ht`DJ�J������!�T����O�9���Xx\*tL��'�40:L�I��J�G�Iw!l:\*�c�T����	�?E�9"T"�)B�$�ȥ��jT��Afw"F�Ϟ�t���X	T*�B�BE���ԬTɫj��rM�<�EA��4,�s�iH���H�F�LE��X�Xb,�|����V�0"�J�@h�.�#�@z�L5����ljFƵ�e�r��/��?��.�ɾ'�hX)�8�&�d��o�p�(��lV� 	Ӥ�`���*�QαG�=^ɱ�e�u�{Ԅ���h�V�J�<�P�=ªA
�H,����g��&)��
*2���EP���`��YtiU<��TO�/Z����Oz(�9��tY���\$-q&d9ϔr�$EfMpX.Q���Q�_X-�_E��V$iP���R������m�5�̤\<�E�e�53�Rc*��,��U"��� �b!S�4f&� ����8�a����ұx4��)��ht8Iǃ���4��F+OS���~P0��D2�G����ӑ`pP��[JG#�G������ďǒ�t4���1�XLȦ>�F����x2�$�j�j0j :�np4z�LF����f2�eM���B�Ȱs�A� ��A����n��Q�4E'5@�eAT��D��EMR�%�s�\�c�It�c��>T�e2�N����m�|��;���hdh;�w6��*Tg�h�g����{��Ƕ��Uz�DPɩ�S��́F5����h�Z`�1�k���PQCD��e��`�hx Ȉ!�0�ѤP��Q�K��(F;�Y���5��֓�ć�aP>Y���j�\%	R6&g��pfFi񆡆�T1�͢<fVZ�iЋS'p�#����4|���h_�	ѣ�8# �C�
A{6.
��1�����	�C~�w��Z&�f�}��|��ˉ���>c�v�_oߎ�7/����|K7aK߆|k�"�����T,|c��@�\���Zr�[�2�s|���E�5>Ӳǉ���t7y��L|ꕌ���E�����I�aE%��v��ة;ɫK*'}�1�&��%�;��b�k~;�:S�;���u��!�j�ՇL���<|�tu���#��:ܩ���\�0>�����2��H�֘�35kw��rQ��+i{Y���I��)����Nn�%��3�r.=9�h&��G
�Xָ�C^�ܝ��M�����<ŝ/���hm(O����s��+5��]�\�L���j�'�1j}�"��b��璜�v曍"{�4!.T`��4n�jz�^.�%=%
�J���*�)k*E�P���˦�ao��6&(�)>K����jNԤ��\ԣ(�U������:i*S(Jj�l��&ݥm�I�F�D�|���	 %�,۞��S"Z�C����M6��Eö"�%N�b䤏�-���ʉlm���Kw����֨U�aM/�mi!v=Ѥ�H���Q��<dm
 ��؛Ϝ��Nʨ�T���*W����M��>�ݘ�Լ�ed��ؼ觼z���ҩ�}Ν5�1x�Q*QĐӷ*EڽZsgsAծ��m`�xR.�}��*Wʅ��U��A�^V7Z-�I�#�S�2�+�2��Rx���������f�����~������.���Y])�`4�P��.m���G��þ����I0�N�փ 9���@ԫ�<��*K������la㥶�7�m�$���FMl(�΋6�E!��k��ݵ�j9�Cɝ�V��u^Z��|sA�Sz��k�T哅r�7�Rٔ�T��^<���Z�g�uSr��m)3Y��ym3U�I9�i�dS�<�t�d�'�|ˢ��b�C�gB��э�d�7u �F����L����f�)3�/���LBt�j�@�ޔ��f�I/[CFh�۔�<���栆z-�*�>&k5�QN4<����>��i���O�!�zt��֠7H���#۪6�-T���Ř �P�"��-fJ����0W̟2�M�����Հ���v�B?e�F���� �q���f{Q��w�'Z��o��g���\.�Z�|k���_��;����!k�4��	f����(���pQ̂��
�v"V}n�����H-_qċ�>|}�6�X��r5m:?��>���zٹ]Y��	�k��x�́������!d�<��Nk+":h�WXK?z����G;���Q������BM�K�t�ɫ�sEZ��ޏ���a��«�ڀZy��f�_�[�f�#b*�ٮq%�[�SتN��l:���F�X�٤R�`3����9!���2Ř�M;5?ꗃ鼾��6H+o�ԥ����g�A�3��Y);�\45���y�H��k�F5+@:�~4R�@��#���{=�=��p�响�)�mhᛞY�q9�F���XC��7�_�򍒚�V�M1�%"�?���d���v�Q�)��k���*��
X|��+O�����M��&3L�ݠ:d��$g,� r��Am�9!�#�E���;��IK&�j����:[��,M�,�Xk؈l�RUou]�������i��i3���FW-�4�^s����u����p]j=Ve�C��O/I��24h�%�:$��8e�y�o;���7��6���<�V�f'9����;o�����
�.�i�[f�*�)F����ʍ�<�Yt/dY
a����m����Aޫ>�j%맭���vg�;2ury���hNˎ��Kk�?=q�&mu�;�<����
���������sЙώ�4���D�L����c��q��'inv�{��Y��R`
7}:�M����	N53{E����./<-�ڊ~����o`�{y��
�΋�мS<��"쯤�W��S|!fx���v�Q����kz��2��of�l���y�cY܄��,���q	ñ/[���\����ju�H��&Û�?�`�0����3����(fx��l���~��3H3_�� �UfUV.e�����6�fx�܉�_�v�i�7��Ku1�E�ıV.�k�,C���k�Mo�ۥɣc����%��3M��ڮ��2ih�i�ڭ]�a����5� ^k7����U�8\�>!�z�,dn	�M{W�S�0��V+��v�~��ca���5\�]k����U/.v�����n��w]���U�ΰ�,o�q���+�V��iߏ硲�,k����G�w�uM�e�]���uvB[�G����c�k�'W�Y��'{����U�;Mǔm�m��?�!->v��K���n�y��<�� �:6b��jy��D��(�F^n�^]�-df���R�f��[�,}�l`���Q=��7�l�6����A�t�Z̍�ih0����i$0�q���9�M���c���O���]�k>�Lɫ�R�l��=���-�	,���z�����:b�Ɋ�x�
]����l9�7j�7�л'xӢ���,�=���h�[I�Ԣ~ġ}9�m�r_:��_��Z;ۤA�&;+�ց�):�G��ZfFV�����y,>H�Ñ�X�?<G�������t�Yt :�?����/vzہ�������̬�f=���]������.����w�?����8���������5��߿Ɵ��_k��~?���x?�^�����w���=��~7N��wӞ-��������&�����������w�n3>�9L��'����8-7��/g���Ie�?���\"�����Lt�g���]�Ⴓ�����Lt�g�������>w���<#���I���8#��?3>;�'���\�oO����߿�>�[���|_���#��>?#�M޽<���3�R���,�k�:��6�����w�/�=��}��������}����7h}6�����;�bk���~Bu<q���0^8n*���u�u5�S��.Q1]m�$�g�~�߳��l���~����C�-���+��Fw;���ĪZ?Y�������oS��S&>���TY'珛�h#������/nw5�.x�z�ё�����g�#����>&��C�qEϵ�d]�vo�����v����-���.�������ss��m��a�C���88��7�*6��Æ����u��u�(�Q-q�[X.d����S�ik�PǬ�n{4�>j�}
o��좷o�m����z�x�[���=��㶇9S�6:���c�&YN�hgX�i�P�fN-�5�
/�d���cc��{~��?3Dؖ?�!���7���?
L��$�:�{���.�L����?�{�������/�rf8��~��ss<�ֲyyF��4j���y��Ι��z�i���VX
>E|��4*^ھ:A�g�J��k��jk?�/n�	1
��
8�^#[w��-�9~�S@� 椿@]�.@G5s�~�̺�����u�\>�ȝo�ߕ����ն�$/���Y;z��ӛ�W��4�@�»�3�ٴ��>�������6�2�ٻ�I����������U�g
%��
����0��_T�4��^� ���;���.c8W�2��������â�˥�� *�G��Ͽg�W�ɯ�ņ׷��K�Eܤ?G���K������͝�{���ݻ%�� ���}H�>b��.vzA�`����!���U�>��Ҩ
�v
]��'���W�o�����Ɯ���CC�xz(
��ٵ|f��ǂc�{���BX=�39�%��$�Z$լ��1=K�������=��k��߷�9�Xs�8IKl� �Hس�QMY�Ը�1%���C���.��J�>W�r̿�$���{IΤIڿ�q�FM^��$�t����Ã6���d����{�Yv汓F)d��M�
϶���o�I�6�{��d�l�1ƥ��1>��,q���x��ƸUYc��l|`/+VK�{YahU��@?���I�6�?�h�ɬFp�L�D#��x`T����E�.T�AU*BN����o�k?�y��&��k&��DWm'ٮ~'����,h�͂g�Y�`6�h3x{���Z����g�
��-��LfT5�U��h�>������gL�>S
ǆ4���)���K62�j#������Ȩd#��6�T�F�k�Q��lT�s9�?���yj��~#�O%���IgM��tV��pD��64�(4,���T-*ה\4^i���s���U����4�{�g��u}:GӨK�[�:,꣡e�d���R��,�7m��S\{���2���`k�KHX��ּB�):Pc��f����Ry�Se���ϊ������6jVyFͪ�U3ze�9�nU3��F�*ϨY�1��@"���L�nn��e-�8ZK&��A�րIDk���7`��G�5`�0u2��3ٶ�f�>ͺ}&����ۧ��d�>���m�g2r���&+ج<�Yy�d���4+��<`�򀣕LV�����0y@���1|0���}�0|�������lWx0�+���2�%�G��Q�8FU�cT2�QU�T�f��5Y�jd&�Z5Y��@:����蘰�-��y42H#����`:�pX���;�:?ݤ��җmh��$���K��p$�S8g�H��F�x�媃�`*��ţc,%�M��ɦ�dZ*��}�X�Vԉ$�jv�j�}�JUF��e��1ȋ�7b7N�)���T�� $K)�b���ł��KDX�p�фS�T��n��`_�Xs3�QYGa\���-��#�7O�e?��}�مY���l~�E�v����Mr��$��"�"u����.M㫳<��vy5��i$���X� ����+��$�+�)f����2�H�
���Mj�Ml�������}� �|IZ>��N��5�:�3I��5��5����`�-_��d{�l�$��Y��4�4��j�&����{���{uY,y ����=�L�s�X?ws����!��ʹ*����R�oڬ�K?q�گK�w̹9���]��Ő�&��H��4�b��㑑���?�/ΖN��	p�e�	�0�in���D:��35�0���H8v$00���'
�G3��.^��p���&�A]��4	�Q�e���:MB_��:�YG�}{M���$�4I�9h��3	�����:��I���f��8�� ���tɪ\��6E	Z�v'�\��1S�D=Se��P4�>�` ����XL��3?���3r����V��шV蓙z�d*q�GqSw��(l�oѸ�ԙ�	�y�zHTsȁ�x�Fe�oh�U?
~-ߘ�*�>�r���98`�}��\�!�$gB2�(A]��	�Q���cns�@t�+��Lb�2�W���$o�K�Y�O��x�a��y�Q*T,=�*#�E1��*!�_�0��&!�@1��*���*c,	U���*�����P �����35>�	|y�// |y�// F�at�^���X|z�^����X|z���cC�DHo��B-on���I�v%�EM*��6
����`��-XC�����@p�}
��/���0�Gה�� ��y�ܱ5e8�����a0�=� ?���%`��An|��W�DO���M�с���`~��h�����\��&8����y`����
�S2�vM�>�Ӑúl����]y�}����y�p�* =Q�z�+���Q�8<\.�N�.`
��q� .CE����/ =3H?p�� �}�8�r���p�<�Q��<�'���S�f� �D.�C�$>�+�y��"?�!�i�2�<p����
v������(�����.���KD�E8`�s�c@�������Q����K!>�a`�	�l�+�%`��8�bm���>�x�!�i����KD���=�>`�9�p��p	x��$��!�� �>�r���"�p��?��y�z�}O����y�*�"������S���!��./�>
���?px�\���~L�W>��C�h@ߏ#��'0����͟����9���yԏ�'P?�M�y���#����E�L�2�
��"�(O��W/p���5�� �瀇��0�눟��`?px�
0̿�r.�?h�������!\:9��� ���wQ~��G~<���}��)���џ��|6��N@��� �W����?A���W�N,*���\�3�旑3��.��S�!����By`���k��u��+߂�2��;����| .��W�W`���(7��?������Hp�;��t	� ��WEz�D~��� \�w���p�����������ǚ<����
��u�+��oYW����֕E���J�I�f]I維+@ϵ��*p��J��ѽ��C=��
p�]�J_�{]��߳�,�޷����K]��4	oXW��7"���|�.z?�s��(ͻ?p�V��܆��~;�t��݁�����`/�z�!~��~��q��C�J�ط����+�'�>�����G`p9 �N#}����Dx`s��sh]��$�YWN�Fa�'i�	>p%���a/p.��\.E�'�'�x�]B/p�!��)��#�J�I�+g�����"�.y]� ������Gו	��4px�����%�֕ß��u�̧i��P
�40�"��.��y`��Y�;���
��y����W�=?\Dz���Dy�����"��k��3�?���S���W��O�ϣ����s�����]_�~`p�.��U�<��#�_��W�)`�+��>�<0\��I�
\z~r�@x`����E���Һ�]���p�䁞g!�.S�����@p�.���E�*p��<�����)`��<��\.��!<0\�=���������L�s�E�p�\v�	�����M`
� l���?F�h�'9�2p�
\z�a���S���M�<p�\$��!<��z~vC��\ �!:p�[F8`
���4��>����s���`
�� ��s�e�Y�
p�
� ��&�+��~� =�>`/0S�	`��｜�~��5��p��\v=���^�
��
����z���>�<�x.S���<p���������?E�*�\V�K�9�2�,p�\^ v�%�� ��F�@�O�����!`
8���&�p� ��. ����K�%�͛/ ~����c��א~�x�����!��h�����U`�s�}�y�a�0\V�+�9`�_!�@��0�p��H?�J?=@p�\��+�	`���<L~��-H?�.��(��g�o�~��c�<0��. �K�s���s�p�U
��9�������`
��-���S���&p8�@�+�e��<��-��{�!`�N �M�"�p�@���p�e
�l�~�z���>`��H?��恧I8Or�s@��#���"�W�s��_�<���G�����E�%���Q�^������p�
�����]��\"�P߯�<VQ&�]��2O��e�
���`�E	���зUQ��ү���)�������+�0<Kt�"p�����R�9��.��U�0�MQ. 灗Hn���~����e�9`�����E��V���?�(M�p�
\�ޥ(]_"���W�
��<\.ބ�_�/��nF� ��
�w�}���H�"��!�2��H�XEY ��=��*p����v݁p�e���N�.�Q~���(������E�S{?p�l�C9�W�~����g���#>p���KD?�t������Z�ǥ�fO�
��=��Z�ٷ�Kw�P����l?�uZ���?|Ǿ[oQ��!
߾�2A�Σ�=���y���@g{��;ݞ'�v{�����	tw���).L��s�������.I磉I�]�d�+�\ �m��:
�:>K���� �;��j@�oEz���[�;��|����tw{Kj2��Q���o)�5=�m�]����'���_�m)�6�G��@_ �{� }a�S�ρ~	���|
�w�� Gy�r�}K�(�w�|�����-���g��}O�-����ۏtOt~}[w/(�n/$ ٯ m�^ۉ�>�R�o��ä糤�3[��}ϐ�����{���g;������`�
V#�D�L"	���:t �����S�����)}Œ��^Q�I�_n)�S~(��c[ދzN����C��#�E=9�M�������?������m)��[t���~�u��F��m};��Zʇ��������"\��:�mT9dC>B�3�����u����jn�}�k���i)?�N�,oԞ��W�/� �+��M�4�Nl�*����i���1ɍX�󋿋>�����B���ch������F�'���7��;��z��ز��Rq�����K���;���?`�6�||�Bɖ�͎6�ً[�;\z2ѿ\��/���Ϲ�C��T���I��;�R~ښ_�Μֿ���� ��@��t��~	�zR-e�s��;J=�c��R�}�5��`K	��{����������Ex�C����n᾽�8t��2����t�
}�GZʊ�^;ےQ4��n����DP�O�|b��t��ˌ����ӓn)�:�(�3[�9�OH���2�R�z��w����������O��ʛ�ߋ�=�+��?|��-e���Af�眞#j���/���r��z����7h�oǵ�N��x��1j__v�ׯ�w��G7ɯ5K~��z�����8�I��l�ޡZ����&��[�/���
�x��=|\;34���e�_�����ӝ�:הk
z�Bg�?���`{���p�뼄�y��]S�����ρ~�!��f�]��c��{ޤ;o ���?��Nڦ��#�lv��nzGbM�K��迶���wb�K�x|(���һ��P�y�пj:�9�z��^���U�c�F��	j���)Փ[{������e��a��}���1�K��z�'���T���Y��|�ݢ}���������[�P�ٺ�����-�P���wA��:s�S�Aл��<|r�����)�C�_[���	w���U�K�gM���>� }�~"<���l݋����ye���#�Ofx{�/�GT������{��c���@����3l�����y�����7�Z�_�e��§z�:�K�?o�'(Ns���_��gM�l>o��X�lV9���zs��	�',t��Y������ː���\�)�_�,蟐68��������@�x��Q}��
���;e����
�[�X�;@�n����c����AO]��~�A�+���
�ג#�v��[A�����>e�K��O�>��K��3Ǻ+��n�w����J��EF�W�wzw�����`o�\j�tw/���6:?G��]��(�{�1?��s4�$�M��KJ���{}���a�ob���Hw����*�s��Oߎ��.�c�_�/�.c�y�.{���]����|~��y�
��F�?>��!�� ��ޱ�����3�������x�y=��������6��t�5m���������Շ��'�;spM�l��Suh��m�AG���й�남?}k���˾�Ƿ�w��-gB�+f����]��)����![YK���#���d?�?�iߧ������#�~�C�??�������6�>�]�_ �ڹ��L��&�=}��Xwvnt>���Ϲ{��?����v���������~�_$�{���L-�π�_�b��/�c���7=/�I�}��|s��N�?k��ތ������������v��m(d�?�}>���%��~�������j{��}�Q�_������v��[�\hM�e�9��ӽ �A�7����]�vكA�0²�OJ�=��~��m�u����v?������v���Ν׶}v6����G�l�P� ��[����������ӛ�i^=���|	j�x�����2�c����S���z{dM��e����?����]ϰ��Ň!xtM��v�s@q)�gh�nlMy�e|y��f����F����ž�t�>���c�}Mj���&[���<��;f�/f��3$.�1�/�' ��bW���3�˲�_��/�=.�}
�9���f{�L�2�7E������m���ojQ�Ț�%{y:գ�иz���?��Q����/�1�;���%��4�t{��y
����3��,����S��h��U���ה�;�Jj�GT�g�7&��)�(m.�ֿ�[�֔o���b��u��R�����5�N�sP��&��#���`�~ciM�:��;LG��=q�G��YSn5�ςJ�y6���j����]����>e��_�Wo \oF�����A�9L6����5�g7�������LO�~�#����U�a�蹔[S�V��}���;��*���Å��Vڥ֊��~c�i����
����ƞA�����_�������^C����y����=���^�;� t���^vq��5��cCg/U��8t��B�+	������v?oO��������?�7���]���Ui��5�4��
��k?��-���������/�[:{q��}~0t��F�=CCg���m^��=��<��/#s��^mI���,��&t�[5��^���$����1d�2t����>���Q}9*��{ԫ��h�>��K�>���[���%d/�q�v�G�^U�g9s?�^zOx�+�w�s8����ʻ�����+�6y�m���.��{V{����\c��P��{>:{�d/~s��E�#����%�z�G��
��5�x�\9�>�E��5�)WD�p����\��C�e�qH��'~.�s��l�8z�?���W��h��S��>���`�:�&.��a�Eq��?�W�Nw�}@v��(�����2�O/��K��������o�w�U����@�����9�tz�3J��M����u�~�ҥ����d/�m������X��q#04�����_ n%��G�Uδ7Yboك^�Mޞ[%B	8�Co�'���ZX�����=}��$c��'��5����������y�[�����^��)�}��q��&���������h�je��\OE��������٫=��q?�<�S��W{�W���?����P}V��Ԯ�s�k��o�^�'^��Z��th�<+b6����oL]xj̾��1z(t�O���W���|6"���|ļ���O�g^�#�|V��SSI�T����71�i*���{�nN�KS��5ӿ���/����}���	� z�3J_���ؗ�ڷ�������G��z�CQ��A�!Nϯ[u2�M#�����[O��:{��^Ʊ���9���7��WN�b�
y&}��~�g�+���L�ZF� ��~�$�����.��ͥ��O"}��N5���\���Pw_�������������79_�F������g蝮_�;ބ�Z��6����O���4���٤����Ps��wJ_K�|��H_J���Qn�ީ|qԑT��D��.�,�׹�/$����?�r}j�w��@�c.ק��Q=��q�����r�I��E�E�t����w�W����~-�+{8����O�:�qEt\�'A�X~�r����[�I�ӥ���w�7��������z��������O"}�K�,җ��/$}��������O�:��H�E�D�n�'G;�fg}黹�H���~o!��~�_?V��H�'��Ĝ��Ԙ(=�q57ÿA=\�tdao?q��'.���=���Q�z��ҧ;���?��&�u��4�g��K`�*_O�d�[�>�:��[�GQ���}b��`y\1=?6�kH�`#O%y��<�ظ�Vy!ɣl��$��W������$o$y�E�@�c6��$?b#�\h�����m�I$?`#D�}6�<���ȋ��*� �f�V�W������F~��+m�M$/�����ޟl��ϫUޓ�6�,���ȧ�<�F^��h/���$ϰ�ג<�F~���6򣋌��*?I�Dy�b��6�kH�`#O]l��Vy�cm�$�����@�6���F{m��%y������l��I~�FYb�A����6�$���"�>y^��_�����+J��/�����F����O��?�W�țJ��9��/��o#oO�6�$/��g-1����O�\y�����$ϰ�ג<��/h��A��ط�O�|η�����[��,5�k�7u�q}.�����׳p���,�}k����oͷa�q��y|�Q.���eF}��i�̨�m���Q����eF����[f<_��/Zf<���Xf<�V�[�ϻU���>X�^f�'V�i���X�uV��^Y��/5�7k�z���U�Uj��V;�J���*/)5�����F�b�ז�WP�/5�;�u>Zj�V;'K���j'��诃��ѿ��2���s����oa��X��2ß�ʫ���*�[f�KV�
���t͵R�7�)݉,����{�_.�����a��xRY��Z��>q�A��̘������C�������A�
&��\�ft@����g[�)}
r}�f�G����� ��/��w�O�s�O�~G)��5�xH>�Q������q��3߸��?J�K�'[���n�/(>�z���y?t�r�����o��'�����������$���ü2���T��?i"���Z���Տ<̏l��=���8�?����~�O�<�DO��4��ߔ��{?L�x�˶p�y'{�|�1k����f�A��?ѧEZ���$�%yF���I����y���R>m4�cv�<-���~�D��d�7��O��R��t{I_?�2��5��ɳ�#�k"}�I>-���c=�$?�����$�%��
��Īӈ��"������g�E2��:���}ڋz��"�@����[����<on��n?���F�F���u\�Az�dc81w����)>�����Oٷ3��xz;D��wx1�u|aֿ�=F�}�O����$?D��A�U����ڿ����1���p��Y�*�C����E��t=��� ��C/���9<ȓֿP������?H��"�oɫ
�۳���8��w����7�I^G��v� ���
�]�~{�����/��\����y�`�N�;�Ke��g����OW��I�>�[��]�?n3�w�����cp�>���<+��|p��G>��c�T�7���i�ǀ���3�����3��W��C�?n7���#��^:����������=���i?�_�ß�jp��7�S�
�f�O�"��������o �#���L� ��.��pC�7�q��>�C�g�L�O����C��
�/��;p'~x
�n�� �����'pm�1��k�
���
�6p�3����;�o�pg1��&����������f�'�OW��O�_n+�?
�?$��q/'�L�����?
���=����G��\�j� %����
^N Z�Q���7��3p'^�/��<�6_B���"/�^������y9�/M����F(�r��TE^�������~�y9��IE�?_N�����y����}����>E�?삧�x9��jE^ί����u�y9�n�"�,�#*�r�܃�|�[�L_S�p<�����E~<�1O��w�z�����C����m��D�*�p��������/c1.R�?�JE� ���8�W��xD�_���U�ܬ�W�x�"��[����Q�7��G����A������v�*�;d����~o���}��w��gE~7��(�u8vS<�}үyF��v�|��Ρ��� E��l�/p,R��q�"�(�%���O�)�����������}9?��"/�k�����Y5^��Q,��~��}9?|�"������)��W�ha��N�;��ꕊ��|�]����}@���u�G(�{�T�_ ���|1��-�� �+�U�^U���U��|�"/_�'+�����m9��k�����-[N�������>>����S�>�:����i>�ح��#w����۪�>��[�ևv�i����e-���g�byf�+W,�p{OSy>��O���ྪR+���G=�V���O~Qm}��=ϩ��m��sj�E���֋v�����W�[^~��7��e��1�&2���1\!�����-bx�c�U/�w����e<�-�v0����>���>��O/�|
�k���@�����A4pQϻ�2^����{^m}���x^m}���z0|f���cp�ϟ��m4��^�־M ?�y��������>�`�i���;����C�������݆����Q�{�����nζ������gr��Q~�b_
\>�g��	��F�y����ep�1|^��C��	�F�? ޳�!���<?]�O�v��/���=?��/P{~r�Oܮ��MW�]Ϳ+���j��j�U��b��
�/ı�YL�"�;>�c�|ך�_"�Tp2�/w�/��[��w���p�~<c��9��0|������/�1�v3����O�^�OE�@��j�C� �y�Z�����w��� ��v��!#�wۥ?d�;������[�_.��_z&���70���o�e/3��v�1������o�po2�Y����oP�Ǣ���U��r>�+^~߾\�Z�x,}�eժ�cnv�Z<�%��U�ǲ��Z�x,��{�� �!�/�����d����܉��;��+�_�;�7:������c�Z<���rw�œ�n�:�x23%�S-��Bp/�;6��������6Ï� .�io� ����<�>��f�O���:1�D��e3��n���pk~��_��R��R�]j�^>��.�x/'���V���\��j�"2���V�Qn�n�x�6�V[?�\�n��S�����p_1����I����U��:Ɵ��=��a>Ò��c�b����c��P�	n1�/��ܦ:��kσ{����׃;�����/f���]�
>��{��=���e�������������j߻��
��W���ϥ|���>n���~�m�^��������_)�1���_����8�/u? �;�JGx��
gl������C�c�s���b1c���e�od"�3�
Ʌ�i���Dq:�I��2����sj�V��
�m��3����_f��_�x�1~������~�qv�5�_�xl�z0�
߄W�V\ �������;���ƅ�c�Q��Q�0����1��)�JCоA1���C��BŰ��E�C���+���R1
��e��r�&�oܿ\�~����<������3����/�9��,��.��3���=����(�?�c�?���A<���t���0�1�8�g��<��G������~��S�#�q_���p]����O:m��a��W.���g-���w,��҇+��җ*��ҧ)��ҷ(����'�t�}mP����J����H���G�b�?E�D�_C�&�A�d=_��e}{t�Y����:��ʺ����:��ɺ����:��'H]_��un(u_��JTꑣuA�s�Ǌ��G���Eo ��_��]��!ȿ��|鏗>u���m韖>f�'��^鯕>W�7��O鿔>H�G��@�ϓ>9�W��1�ߒ>��~����#}6��"}'��!}�!}	� ���^.�ֲ~,븲�*뚲�(�|��&�^��$�@�#�"�>!�R����ԯ��<Z��;~~8�U!n��q�T�;��J����Z�^7|�T�k:�ѷ;/��|��Q��O�ju��I_�q5����ph�`�yP4Zwh\�`WD"K�#UK�U,�TV.^�P�i�l�Z�dqeE���q}yC��-F�ܮ�x�*ooj�h�[o���v4�oh�R�~K󦆅�
}v�����/>J�p��y�
w��e}G8���U���'�}V��>_���:>A�ޙ�����S4nO�~)־�|�Y�]ǽ^�����M/�]+�a��_�k��%���_|��0�������}�o�ǝ]���O����|~w�sT|�E�/������T�^a���|�R��������cI|�B�7T������o\d�@�+����ڹ�y�"��K��;�Хx���	|SU� �g+
�V<��T� !�(f�� .^��W�	m���Ϡ<9T(�,��*�؊5\��%jy9-����J�E�L�"B--��u
�r��p�i{~ߚN��V����r]��GG�t�^g|ɧ��R���d���Sf)�<t�v���.���i$��[SV�tI��P�t���t:-�<M�;�o�u���6jϪ�ܢU���
���uKT�(�i�
ˠ3vY��噶�\$H�2���W!X9RJ��ٹR\V��pI;0:'G^tqf��������U�6ap����@R:D!?�1L.rdeeJ�W��3�I�@af�R2�e�,) Iy�-�ʖ�f�g��t0�!HR��ݎr����]���n
3�� #0
�J
��,W�?��K��H��n�96�͂���5V)~,��_�-�	k�0(�����3�ZJ��ؕ�P�~t��B�̂�,4��oX�0CK�"�߃�+XW8S����G�a�F%�̒����TgU�1ݏ�߃���z�l�:��=��[�k��Wm�+T7�M
��Z:>R?�:��~�#�"�PϮuޓzBݎ�������}(=�Y^�CLeр2�}@��8OEɚ��nV�${Yg��x�����8O�?@�a��̋��ǫ�㢬Β��`�v���a�S7@�\�
JE\=��<UNm�-E��ߦYV�y��Y8h����L��0ӵ���tLL�>�&S�g@Aߘ2|�����'alm���X�(�g�g���a9Xd{w��:�%,�n>Y\v��L�����S��S��X�wVBߐY�������	�60C2>2�O���~ ���L�L�
�)}�#���������km��y�M�#b�[("��_���� ��W~:�"� �8��|��RX�qk�◚�~����ꚨ��X]LJ������preo��.΃z������*�-.X��Zg5Vq͎��%�Y=T�ǲ���9:(�"��(*~����ԗu1@v^��u��O��d�I+�֟�7�|ͱpWM�-\�i�wdHY4�EDY9s��O����y�j�l�
gF�{�Rv�ٸ��ڔ�z��U��z�'9���/|��V�$=!X�B��A�u֘/���̳�58=��>#�8j�xv���^=�io�)�{,ޛᖘ��9
ֲ9JgqM�[\�u���lL(}7[ǔ
@�j6�±p���LZ�u�oe�Ί����p:�ʳ��z8���QL�e] l㹈�M�4�n=���.b�����\_ߕ�3!
Z�o��T�>_)<���N4w\P9��M�������=��Q���7�o?�$�P;֑w
���'�Y���?�
�{+h�?�R��rͬk
��D���b]�A����iwbM�L(}ѷ_o��d����ӡ�����\h`��5������I��L9\v��`JgA����H.kaJ��C�Af��.(�
�[CmҴ��ϨI�	���j�f)��+�I
)��t�.�lo�2�X�u��] Fi�{�~�Xv��Iʂ�-V ��ց%�<�32�Q���哟`J��6Xܓ�Zݣ6Y�M�5�r/k<ƼPe����8[f�����,��A���&������c\N��{F��2�����U�o�e��y�!��ɐŤ�d1�_@*cSls�F������ː�D���A��,����=�݄Y�1U�����:$��÷z��
�a����%� �B~�$�2Sl�{���l��ŴUA�0��,�hP�50O'�7�+��9�)<��!LcB#$�fFE��QL)��e�Mv
I���D�$$C: � IF�dh$aHb
�: �$C$�w@�$7"ɰH�Hr<@rG$]��� IT$ݐ�� ɝ�t76
�wu��3��;���
��dGBv_�vi6A*���{A�G��.�.5�N�[b�Lr�~�����X��
3��A%���Z9���uVni<v�n\I�@{7��͟�A�+���p�?�`4�2��HP����#�o�)������
�l�������}k�[k]N�yI�e���Li	ٷ֙�'������$ط��7]y�\᛾<�1ᛡ<i��-�<	��u�5ط�����<	��Na��-O�|
�N�1tq�j��*Q�Xݓ����:��OK��X�hf�~"f����o�p�7�l��)m�q[;��	1����Pn2�(�G�XChSZ�ʡ�K
ɼ�}fȌ#���3#!�7��Yb?k��3�~��T��|��χ��2��W���g&��3���'�~&�6tT�h?Ye��
M������&�>Ǘ�р�D-^f��t܉�Ȟ~K��C��`OO�*M\=��#�>���S�U,���{�
L>�+4t��:�������yA��>��oy�N�R���<��������>��'�j�@� �V�D+�/�O�}��ǄI�tL�>�k���:4؞��k���8�Y[��5#�Ӱ����܌���X��]�0y3�A6�+I��nf��ڑ"����j���X�<?�8yvoO`95�Te����� %�0�7g��������v�Xr��X��/���c��w@�m�vĬ�<k������4�6|?��\z?�J���X�u�ٵX���4wF�����<f׊>Wl`��b۝s�U�I�����r%
#endif

// Use this annotation at the end of a struct/class definition to
// prevent the compiler from optimizing away instances that are never
// used.  This is useful when all interesting logic happens inside the
// c'tor and / or d'tor.  Example:
//
//   struct Foo {
//     Foo() { ... }
//   } GTEST_ATTRIBUTE_UNUSED_;
//
// Also use it after a variable or parameter declaration to tell the
// compiler the variable/parameter does not have to be used.
#if defined(__GNUC__) && !defined(COMPILER_ICC)
#define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
#else
#define GTEST_ATTRIBUTE_UNUSED_
#endif

// A macro to disallow operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_ASSIGN_(type)\
  void operator=(type const &)

// A macro to disallow copy constructor and operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_COPY_AND_ASSIGN_(type)\
  type(type const &);\
  GTEST_DISALLOW_ASSIGN_(type)

// Tell the compiler to warn about unused return values for functions declared
// with this macro.  The macro should be used on function declarations
// following the argument list:
//
//   Sprocket* AllocateSprocket() GTEST_MUST_USE_RESULT_;
#if defined(__GNUC__) && (GTEST_GCC_VER_ >= 30400) && !defined(COMPILER_ICC)
#define GTEST_MUST_USE_RESULT_ __attribute__ ((warn_unused_result))
#else
#define GTEST_MUST_USE_RESULT_
#endif  // __GNUC__ && (GTEST_GCC_VER_ >= 30400) && !COMPILER_ICC

// Determine whether the compiler supports Microsoft's Structured Exception
// Handling.  This is supported by several Windows compilers but generally
// does not exist on any other system.
#ifndef GTEST_HAS_SEH
// The user didn't tell us, so we need to figure it out.

#if defined(_MSC_VER) || defined(__BORLANDC__)
// These two compilers are known to support SEH.
#define GTEST_HAS_SEH 1
#else
// Assume no SEH.
#define GTEST_HAS_SEH 0
#endif

#endif  // GTEST_HAS_SEH

#ifdef _MSC_VER

#if GTEST_LINKED_AS_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllimport)
#elif GTEST_CREATE_SHARED_LIBRARY
#define GTEST_API_ __declspec(dllexport)
#endif

#endif  // _MSC_VER

#ifndef GTEST_API_
#define GTEST_API_
#endif

namespace testing {

class Message;

namespace internal {

class String;

typedef ::std::stringstream StrStream;

// A helper for suppressing warnings on constant condition.  It just
// returns 'condition'.
GTEST_API_ bool IsTrue(bool condition);

// Defines scoped_ptr.

// This implementation of scoped_ptr is PARTIAL - it only contains
// enough stuff to satisfy Google Test's need.
template <typename T>
class scoped_ptr {
 public:
  typedef T element_type;

  explicit scoped_ptr(T* p = NULL) : ptr_(p) {}
  ~scoped_ptr() { reset(); }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  T* get() const { return ptr_; }

  T* release() {
    T* const ptr = ptr_;
    ptr_ = NULL;
    return ptr;
  }

  void reset(T* p = NULL) {
    if (p != ptr_) {
      if (IsTrue(sizeof(T) > 0)) {  // Makes sure T is a complete type.
        delete ptr_;
      }
      ptr_ = p;
    }
  }
 private:
  T* ptr_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(scoped_ptr);
};

// Defines RE.

// A simple C++ wrapper for <regex.h>.  It uses the POSIX Extended
// Regular Expression syntax.
class GTEST_API_ RE {
 public:
  // A copy constructor is required by the Standard to initialize object
  // references from r-values.
  RE(const RE& other) { Init(other.pattern()); }

  // Constructs an RE from a string.
  RE(const ::std::string& regex) { Init(regex.c_str()); }  // NOLINT

#if GTEST_HAS_GLOBAL_STRING
  RE(const ::string& regex) { Init(regex.c_str()); }  // NOLINT
#endif  // GTEST_HAS_GLOBAL_STRING

  RE(const char* regex) { Init(regex); }  // NOLINT
  ~RE();

  // Returns the string representation of the regex.
  const char* pattern() const { return pattern_; }

  // FullMatch(str, re) returns true iff regular expression re matches
  // the entire str.
  // PartialMatch(str, re) returns true iff regular expression re
  // matches a substring of str (including str itself).
  //
  // TODO(wan@google.com): make FullMatch() and PartialMatch() work
  // when str contains NUL characters.
  static bool FullMatch(const ::std::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::std::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }

#if GTEST_HAS_GLOBAL_STRING
  static bool FullMatch(const ::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }
#endif  // GTEST_HAS_GLOBAL_STRING

  static bool FullMatch(const char* str, const RE& re);
  static bool PartialMatch(const char* str, const RE& re);

 private:
  void Init(const char* regex);

  // We use a const char* instead of a string, as Google Test may be used
  // where string is not available.  We also do not use Google Test's own
  // String type here, in order to simplify dependencies between the
  // files.
  const char* pattern_;
  bool is_valid_;
#if GTEST_USES_POSIX_RE
  regex_t full_regex_;     // For FullMatch().
  regex_t partial_regex_;  // For PartialMatch().
#else  // GTEST_USES_SIMPLE_RE
  const char* full_pattern_;  // For FullMatch();
#endif

  GTEST_DISALLOW_ASSIGN_(RE);
};

// Defines logging utilities:
//   GTEST_LOG_(severity) - logs messages at the specified severity level. The
//                          message itself is streamed into the macro.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.

enum GTestLogSeverity {
  GTEST_INFO,
  GTEST_WARNING,
  GTEST_ERROR,
  GTEST_FATAL
};

// Formats log entry severity, provides a stream object for streaming the
// log message, and terminates the message with a newline when going out of
// scope.
class GTEST_API_ GTestLog {
 public:
  GTestLog(GTestLogSeverity severity, const char* file, int line);

  // Flushes the buffers and, if severity is GTEST_FATAL, aborts the program.
  ~GTestLog();

  ::std::ostream& GetStream() { return ::std::cerr; }

 private:
  const GTestLogSeverity severity_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestLog);
};

#define GTEST_LOG_(severity) \
    ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                  __FILE__, __LINE__).GetStream()

inline void LogToStderr() {}
inline void FlushInfoLog() { fflush(NULL); }

// INTERNAL IMPLEMENTATION - DO NOT USE.
//
// GTEST_CHECK_ is an all-mode assert. It aborts the program if the condition
// is not satisfied.
//  Synopsys:
//    GTEST_CHECK_(boolean_condition);
//     or
//    GTEST_CHECK_(boolean_condition) << "Additional message";
//
//    This checks the condition and if the condition is not satisfied
//    it prints message about the condition violation, including the
//    condition itself, plus additional message streamed into it, if any,
//    and then it aborts the program. It aborts the program irrespective of
//    whether it is built in the debug mode or not.
#define GTEST_CHECK_(condition) \
    GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
    if (::testing::internal::IsTrue(condition)) \
      ; \
    else \
      GTEST_LOG_(FATAL) << "Condition " #condition " failed. "

// An all-mode assert to verify that the given POSIX-style function
// call returns 0 (indicating success).  Known limitation: this
// doesn't expand to a balanced 'if' statement, so enclose the macro
// in {} if you need to use it as the only statement in an 'if'
// branch.
#define GTEST_CHECK_POSIX_SUCCESS_(posix_call) \
  if (const int gtest_error = (posix_call)) \
    GTEST_LOG_(FATAL) << #posix_call << "failed with error " \
                      << gtest_error

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Downcasts the pointer of type Base to Derived.
// Derived must be a subclass of Base. The parameter MUST
// point to a class of type Derived, not any subclass of it.
// When RTTI is available, the function performs a runtime
// check to enforce this.
template <class Derived, class Base>
Derived* CheckedDowncastToActualType(Base* base) {
#if GTEST_HAS_RTTI
  GTEST_CHECK_(typeid(*base) == typeid(Derived));
  return dynamic_cast<Derived*>(base);  // NOLINT
#else
  return static_cast<Derived*>(base);  // Poor man's downcast.
#endif
}

#if GTEST_HAS_STREAM_REDIRECTION_

// Defines the stderr capturer:
//   CaptureStdout     - starts capturing stdout.
//   GetCapturedStdout - stops capturing stdout and returns the captured string.
//   CaptureStderr     - starts capturing stderr.
//   GetCapturedStderr - stops capturing stderr and returns the captured string.
//
GTEST_API_ void CaptureStdout();
GTEST_API_ String GetCapturedStdout();
GTEST_API_ void CaptureStderr();
GTEST_API_ String GetCapturedStderr();

#endif  // GTEST_HAS_STREAM_REDIRECTION_


#if GTEST_HAS_DEATH_TEST

// A copy of all command line arguments.  Set by InitGoogleTest().
extern ::std::vector<String> g_argvs;

// GTEST_HAS_DEATH_TEST implies we have ::std::string.
const ::std::vector<String>& GetArgvs();

#endif  // GTEST_HAS_DEATH_TEST

// Defines synchronization primitives.

#if GTEST_HAS_PTHREAD

// Sleeps for (roughly) n milli-seconds.  This function is only for
// testing Google Test's own constructs.  Don't use it in user tests,
// either directly or indirectly.
inline void SleepMilliseconds(int n) {
  const timespec time = {
    0,                  // 0 seconds.
    n * 1000L * 1000L,  // And n ms.
  };
  nanosleep(&time, NULL);
}

// Allows a controller thread to pause execution of newly created
// threads until notified.  Instances of this class must be created
// and destroyed in the controller thread.
//
// This class is only for testing Google Test's own constructs. Do not
// use it in user tests, either directly or indirectly.
class Notification {
 public:
  Notification() : notified_(false) {}

  // Notifies all threads created with this notification to start. Must
  // be called from the controller thread.
  void Notify() { notified_ = true; }

  // Blocks until the controller thread notifies. Must be called from a test
  // thread.
  void WaitForNotification() {
    while(!notified_) {
      SleepMilliseconds(10);
    }
  }

 private:
  volatile bool notified_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(Notification);
};

// As a C-function, ThreadFuncWithCLinkage cannot be templated itself.
// Consequently, it cannot select a correct instantiation of ThreadWithParam
// in order to call its Run(). Introducing ThreadWithParamBase as a
// non-templated base class for ThreadWithParam allows us to bypass this
// problem.
class ThreadWithParamBase {
 public:
  virtual ~ThreadWithParamBase() {}
  virtual void Run() = 0;
};

// pthread_create() accepts a pointer to a function type with the C linkage.
// According to the Standard (7.5/1), function types with different linkages
// are different even if they are otherwise identical.  Some compilers (for
// example, SunStudio) treat them as different types.  Since class methods
// cannot be defined with C-linkage we need to define a free C-function to
// pass into pthread_create().
extern "C" inline void* ThreadFuncWithCLinkage(void* thread) {
  static_cast<ThreadWithParamBase*>(thread)->Run();
  return NULL;
}

// Helper class for testing Google Test's multi-threading constructs.
// To use it, write:
//
//   void ThreadFunc(int param) { /* Do things with param */ }
//   Notification thread_can_start;
//   ...
//   // The thread_can_start parameter is optional; you can supply NULL.
//   ThreadWithParam<int> thread(&ThreadFunc, 5, &thread_can_start);
//   thread_can_start.Notify();
//
// These classes are only for testing Google Test's own constructs. Do
// not use them in user tests, either directly or indirectly.
template <typename T>
class ThreadWithParam : public ThreadWithParamBase {
 public:
  typedef void (*UserThreadFunc)(T);

  ThreadWithParam(
      UserThreadFunc func, T param, Notification* thread_can_start)
      : func_(func),
        param_(param),
        thread_can_start_(thread_can_start),
        finished_(false) {
    ThreadWithParamBase* const base = this;
    // The thread can be created only after all fields except thread_
    // have been initialized.
    GTEST_CHECK_POSIX_SUCCESS_(
        pthread_create(&thread_, 0, &ThreadFuncWithCLinkage, base));
  }
  ~ThreadWithParam() { Join(); }

  void Join() {
    if (!finished_) {
      GTEST_CHECK_POSIX_SUCCESS_(pthread_join(thread_, 0));
      finished_ = true;
    }
  }

  virtual void Run() {
    if (thread_can_start_ != NULL)
      thread_can_start_->WaitForNotification();
    func_(param_);
  }

 private:
  const UserThreadFunc func_;  // User-supplied thread function.
  const T param_;  // User-supplied parameter to the thread function.
  // When non-NULL, used to block execution until the controller thread
  // notifies.
  Notification* const thread_can_start_;
  bool finished_;  // true iff we know that the thread function has finished.
  pthread_t thread_;  // The native thread object.

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ThreadWithParam);
};

// gtest-port.h guarantees to #include <pthread.h> when GTEST_HAS_PTHREAD is
// true.
#include <pthread.h>

// MutexBase and Mutex implement mutex on pthreads-based platforms. They
// are used in conjunction with class MutexLock:
//
//   Mutex mutex;
//   ...
//   MutexLock lock(&mutex);  // Acquires the mutex and releases it at the end
//                            // of the current scope.
//
// MutexBase implements behavior for both statically and dynamically
// allocated mutexes.  Do not use MutexBase directly.  Instead, write
// the following to define a static mutex:
//
//   GTEST_DEFINE_STATIC_MUTEX_(g_some_mutex);
//
// You can forward declare a static mutex like this:
//
//   GTEST_DECLARE_STATIC_MUTEX_(g_some_mutex);
//
// To create a dynamic mutex, just define an object of type Mutex.
class MutexBase {
 public:
  // Acquires this mutex.
  void Lock() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_lock(&mutex_));
    owner_ = pthread_self();
  }

  // Releases this mutex.
  void Unlock() {
    // We don't protect writing to owner_ here, as it's the caller's
    // responsibility to ensure that the current thread holds the
    // mutex when this is called.
    owner_ = 0;
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_unlock(&mutex_));
  }

  // Does nothing if the current thread holds the mutex. Otherwise, crashes
  // with high probability.
  void AssertHeld() const {
    GTEST_CHECK_(owner_ == pthread_self())
        << "The current thread is not holding the mutex @" << this;
  }

  // A static mutex may be used before main() is entered.  It may even
  // be used before the dynamic initialization stage.  Therefore we
  // must be able to initialize a static mutex object at link time.
  // This means MutexBase has to be a POD and its member variables
  // have to be public.
 public:
  pthread_mutex_t mutex_;  // The underlying pthread mutex.
  pthread_t owner_;  // The thread holding the mutex; 0 means no one holds it.
};

// Forward-declares a static mutex.
#define GTEST_DECLARE_STATIC_MUTEX_(mutex) \
    extern ::testing::internal::MutexBase mutex

// Defines and statically (i.e. at link time) initializes a static mutex.
#define GTEST_DEFINE_STATIC_MUTEX_(mutex) \
    ::testing::internal::MutexBase mutex = { PTHREAD_MUTEX_INITIALIZER, 0 }

// The Mutex class can only be used for mutexes created at runtime. It
// shares its API with MutexBase otherwise.
class Mutex : public MutexBase {
 public:
  Mutex() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_init(&mutex_, NULL));
    owner_ = 0;
  }
  ~Mutex() {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_destroy(&mutex_));
  }

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(Mutex);
};

// We cannot name this class MutexLock as the ctor declaration would
// conflict with a macro named MutexLock, which is defined on some
// platforms.  Hence the typedef trick below.
class GTestMutexLock {
 public:
  explicit GTestMutexLock(MutexBase* mutex)
      : mutex_(mutex) { mutex_->Lock(); }

  ~GTestMutexLock() { mutex_->Unlock(); }

 private:
  MutexBase* const mutex_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestMutexLock);
};

typedef GTestMutexLock MutexLock;

//���]<��O�?t��fJ�yEE5����Hߌċ�A���B��9��k��O�$;��)x\�!RgY��d��� �wR���g�
��]�b+�T��	����\���U\������7(��,,1\�ڝ%�Q��{{&�Q)l� �G`b�v|N�?ޝ��Gg�W��RC�F5+�*�dP��2S��v�g�����{��<�Ĝ����U��(<�G�$�K�u��8�.>T�,\��G�P�4�e�tN�i;
�Gc�Y\��{&��^.�G�e&�O�|�O���#ޏk�G~%��{�۶1��}L~&ʫ.v��O�7���삉؄���!�%�x��"�$L]Xd�7k�����BK�Eۯt�����P2_���6q��nڔ�4~}��^�8'?Ϭ-.F��i5��<��>]l�>UX��P�g&���Ҳ�	�<k�E0[JM%y�(-�/v?KN!E#�d���jME��yl%9(�ūGx�ƴ{�-�))�hٵB�M2�̓����n�>_t����XJ��}r�l�b�-7�RB1��,���h�
-�R˂K�U�X$O:�b1�J���z҄�Ʌ(9�[ ~^��Rq������.�?+��CA��K-���2Ȥx[iI|~�����a�Òb��
me�
m�<ђ}�\�K|~�)���"�p�S�,��X~qwZ��H����	�X*���M��ؖ	Jv�g�@�yشh�[����0hT�]
�;T�>�@�^����aЍ~t�k�,��V�[�� ���@[`���]ka��U�
"~V>L��j��S�W��t�^�а/A/L�� Mz(�=�M��:��@G~�``8���ё'Ah>P���
�
7��Kg�Y�
�A�!��.�|C�xuoįL�!!���:�n+�'?M!� �Q��)���������-���F^N�������3��L��=�߄�)홐4,ȟ*��� ��k�L�0�0�<�L>�Zw��byl�A��tP^<3���Y�� �����"�x����v�%��Jg-��*��H!��%]"b�2<R����1
� O�M��1Oլ谙���Xe6����
�׷;	���e8����ڣ�J���q��,J9���qa�įD<���8����Յ� H�S;�	��|W `��_y��ѤP��`R�/D������'h����ю���
���q���HvO���|�A�?�,��b�4u[dW8��1�� �"i�B��r������|����t.�G	c��I��t"9�#B�;�;�;�;�;�;�;�;�;�;�;�;�;�;�;�[�Ix�_�����$��[�~�p�$̇���0$|�@x��ǭ��s	#��kH���;��.��!ar4��@x�Q]|���}�������m��������x�����?/�a���t���.�t�/p���8��t?�'9�(�(sC��iN�q:����r���U����[�nⴖ������b���8�?3dH�#I����?t�ْ0?a�#�LI����S����Grr�}�K~Є��׽����5��7�ו�U{ý|]���he������ו�������u��F���|�|]���hc�����U���m���
����H���u�}i�_��_�V��#:�/���u��Q������x_�������?�n ��@����M�a7�_׋�ٱ���u��®[����7ܢ|]/^����*��4��U��������� �����J�i��D_y�Q@@|]�?I�q�_w$��s�u[9�U�����G�׽Z����5�R|�]��
�>4��V��O��m�����D)|�H���O�����n�|�����_Zv���=��W[�竰ވ>E]Q"/S5ϛ��!��Uv�F+B�
���k�X���zŊ�cV���;�EJؙ�S��G '6�����D��WN� o���T�WN��7S&�Ձ?�g��S֯��?����q��e���������B�������^��^���}��	���kS���������O�}���~�}_���?k?_�q��	��Ȟ�ļ�1ڮ����[d7��7�hR̪?�Żo&�_����7���_�ݨ�8��c�F�1�j <�� �A�� �v ��@x�����CƳ
���Qu�''@�y��+��c�o�������gU =��� ��?���c
*;ז�/����Jr�v�z�)Ei��#�s���%%yV�P�4dL�Pb)(Zli�}ه\Z�c�&��Gt�l,'�S���ܜ��s"��R���O{�λiXR����KN���/��y�<|��A=9%��"���e���YL6kQ	�o�/1�۳
ڳ@1d�ZG�P�raG����y�"�\���ȏY�c#.�@�|��en~Q���K�"܎]j-�3�%��V�=��V�˷��s���e!�,��A�d�f�/��K(&��v��*^��
3�3�t�&)`��T�k.�p�k��/������B��[u�~��m�$$��؏ST���,��çVi1�7wX�mAA^q�`���/2	�E�ye��h�
� �(y[�a��,�M>z3�(soTJ��E����A;�>/-�K@w>
��5*�`�R���pL�W���U$O�P�ѭ���;I�g�}�z������%wǻ��Q齌/���I�H�e|��j��?L�o��G��|}V��%_���W�12�|�>AƗ�&�����T_�=�AƗ�-g���=�,?L>����e��2�|+�XƗM(���{-�2�|=g��/�U��w��d|��F�e�����/���=������/?#P-����w���%������}�v+��+�[���ne���v+��̗y����	d|�|6R�Pn�2�|oW+�˿������E%��1r�����_Ɨ�k���ۿ�?Hn�2~���e�8�����r�����/��ۿ�?Dn�2�|��JƗ��������e�d����)r�����_Ɨo�V�����/�?*��1yy�U�AoN��u�A��*~�?g3�}x������#���w�W^4��]t�-@
�Q��=ݱ�~r�Fw�����O�J��J?��;��O��=��O��=��O�n�N������R�ɭD�0J?�/O�#�~枬r������Q��t���x���;��-bq��['�j�y������n���+}��}�����k����F|̠�5칎SA���2��__���A�`{�`� ����>!5�b�@Ļ���% Cq�}|��P�c�-����^1gPg�U��R��l�=U��X�W��/+
n \Ў�4c���~j^���o�����$�%0S��G�aA�AV�n��(�-������`ǁ���$�y�M�����O	��.y�uzq�%v���N\J�G;�^����Q4@�'�����)JmQ�eJ��[y�J��9���nH�ֱ/��DPHQ�B�2[��2�	]��  �+n�(7r�iVπ2_q�-���#��b6	���T�5�+v`��V�h����ŚKtwm������;�'J���Y�������g��ˁt���]3x��b��Y��5T�����w0]��w⹼nzbu���̓Kp�q��"$�ap̝�Y]�ḋڰzi*V�AK����p�
Vn��7$=�Y�ٚ���o~b�~
q�����y�㩿Wb��KV����P��?��*^�a�`(���C��q���h�����=�}���,I�`(�_ow1�י�އ��۷���!TP���!�V�c�KH|�Ø1�~�R�V�#�EuJ|�,��:�'�����
��ڍj|�'�� ;-�V�íT#?�.���S�#��V�IQ="6�a=V[�g���frigHMsV�O��x���{�?��=��a�_�Wf#�Y���3h�z#��T���,�����f8��|a
#�{�� ��H�HL�����O�zq�4��OKU~/<�h����wJ�o��/d��U�(ꨇn��$~@�%�qM'��x���H�j�3A��ⲇ+ǺVDe~'�. /��,�oW��F�3���]y�Ӿ<L���$0�H���a��5���B4*�W����CU_Ë0SJ�q�ϼ,�6�]����t�A���s�9���� BI��/�CW��c�4ۣ|!�1��|�E��y���HpT��37��I�z�_|;7�{%�#D���b�ª~�-o�-�RD��@�k�<(���8S�G�)�>��Z�0;)�o%�	�݃vCZ��cX������緥��k-Тe�x��[<U�-΃�N<D�����/��1_4�kq �\���2�ꗥYWҙ���h��9B��ś
D��f����
�m;��t����-�sQ���c�QP`�� �!�8_=Fg~c*%o�7�^|
��j@��j@갇��?L���.�/�^�WP:5+�M��X�=��'?o�G��o@�旔�4��E)�����`�\����t�#��Ue�);����A���r��R�.^�NAG��0F��I�Bڢ
1�{�Q�G��z�!���T,� C�v�$˞T�ǁ�����2cJ���7?~��<[�'$#:�4��´ċ�-�/�7��t��4gT��e��Ƨ;��8���GĀg�Ķ��v�/�'Q������)6|�EB�!Dh:��c'o̮�m/�!F��+���`��	�N`�J�\�rta�,�u9Jc��O�git2V���^$'��QqkC��ue)�	i�Ni�˚ӝ�а���33�Y�:[�$*� �y[����3B��[Ob@�Q�����3�}:h�*���@54���3)��9g�霋Cҝ����9Ko&:�$�S�m)�at��H\��	�	�-#&��b�-�$۶ׅ`^���Z�
HyZ���&�wܰ�
=�v�́Z(��|��*6�"�OH(K��,�6k*^X�
B���L�xC���_g+B�O��<�k%��'�:��X���X6���D�J�V߇��ޤ�W��h�U�Z����W!8�r���b�c4�O��J�@�J��bH��/x�=�p��1,����&�	Z&���!�@��1�
�&��ݡ!���4}d�$���P�Q0��m�1 T|^B4+;�Y
��Y�G�r���ͦ{O�Wm��+�J��C�<��j���h]�h�����^j*�Q��3-����k���u�Q�>�s��@��l][�#P��3��9����E�d�28D�����M���L�-��S�}�]jWv�J����)U��\�"��%lJ��T)��7A�5}��1)&���,�.�tB�G;�o��|�0<��gF{F�p���l��@$�7��;��*|V�܊��Ӛ���{����Q��`�돶�|ᜠ����ʟ�
o^KC�Q��Wn���x��"Y�>�kC�:��׿�XA��7���GX�:�T���ڗ���{��?
N�b�dWt&��^��k��9�������j_x;%�NX <��a�����tN�ެ+�RԬ�Gb��ސ�iX�۝6,�]=YqR��ұa�� ���	wa���c鴡e��cӯ�}@��x�q ��nG���@E�J��'[w�+������i�xK�V�G3���e)���`�o	"�5+=�K����Ȓ�r +�==(�:�&�m�d��J�ʱ(]]�r��S������es�0���Oug�:���S�B��K�q�=l7�I�L!-)$����}F�]l%!SZR�bK
��3i9a�ʳ���^(���CȖ ���a�������ޤ�Ѭf%��a���U8{����k>!<ͤ��΁��h��"�W�}�C�|� ����z��Dj�A5M���
�t���k��M��|�|]|r�5��`-�F��ZM J�B.��|���"-N���d�
T�9D+HX�b�ACZ���y7�1�kq�j-����q�������95����Dhԕw�+�`kN�Az�w�5�V����
���o��8ıM��(m��Y���v�@P{�4����p�g ۿ�v?MU	g{6���l�D�=����(����>��xm�g�g�>f�����0v��y?[�vVt��Ӳ�w�'�|�톫b��[�͟�,Z�}|��ws���=4�	O��wD��=�垃���#���!����n��Y��o�y=�"*~���u�0/FB����l��pO/|���/��^����_q/&���πM��m�M��mT���mT��R:���%��Յkl>�����t��ǽ�Tz�w�;r���o��K�;(������ȿ��"Hh��{�����U����~��}��v�gc��ӧRJW>��:��2���&�!"�Ȋ�;�u���V��xD�(���qj+^"�b;��ڏc{yܑ�HkMS���y5⬬8�74:�ka�"�MYiM����:�U,� �<^vg"�Y<�G���U��K���W�i6�18Ҡ�����=�W4�N�b;���xj��1W�i�h��a.��>�&{��Q�=T�]���/M3��,�q�u/�:Z��Y�r�k]CI���]Vx �/�r��w�Q^g��Jk_�e��m����ySxakv.�^qq�	��S"_�pN
h�t)m��ʟF�oR/��q�9��'s��\ЩO���`ߦHWЧ�]ZUm[��tS�2�Qј�bg�4/d���ߴ��K[)���'�;�B���m���x�����\���aަ^�_Ji�mdh�{�����ʡ�d�_�d1^��j���4t<�{^�bﲘ��`oӂ�>�S��Z�������j��5c݆����`���Aީ���oa�-M[�G���ȭʫG�8���C�G����Eg5�:=�kT�Y�`cO\E��
4��v��j��y�����`���28�u	u+W��[�K���^�s8�?�>��4���gC�b�E���ӆ��n��#f'�}�<
�B��x��N�e'	F��vŻ=�H��k>�u����A��0�%.���߄�~	��'hs
��_�มmڔ)��VKAq����Я4���G7
E�DZ�b�bF����i�i������Pd�����+9%ZT�y�h�dϠR�{VbM�j�D�Ȫ]h)��y�X����`.*�hKl��y��V+B��-�~��V!����9�.B�ͪ-�ղ�=H�
��c���!}�o&p{�`~n.��
��c�e�]w��$u�\'�:Ah�?�Z�M�f��n��W;�r���G5�i��ԭnw*<7ms��Ɔ�`8�h��W����{����R2!vm@Sq)L� ��#e�u����o����k���	@�!�(����[��C�돹ݑA���b��@�>�H<�
�R�;U𲄶-0���ȱQ�5�KBʅ��1pH�ҽ�x�dq�۽� �W����ǅΣg�;[��Ż���/P&_{�"�Ou��4 �pNB�4{�j��xo�{E���^"�Wx���H/�r�O����~<���j�" ��ryDc��M��Ձ�,���:�󀦃{w��L?ytgs� ��w�ֹݛT7�ߴ��N�:��!T�I�"��)�d�.�@?�yZ����_��'Hx��V������7Fh�"�tۡTj=(�(?
��5���*еF���.�	:3��������'�gDT�TB>� �U���3Ku�|ƃ����3��@ ��ߪ�5{|����
V�
i�*��5Ó�`?z��d*�FOgm^wȟV	'�p�3}p���p?{2_�x��?3��;��:(O=����o��UZ�5A�*�d�ާ,�!^<�WQ(;�y;/�tЮ�z������n�Ә�A�������i�Y��To��|Y�ۭ���(~�)�� ��y�7 ?���:п�����?|��~�w��>��z�.ޞ"2US ��.�.Jz��/�>9�O?����������������������~�O�����/_��m���5?�;�-������^�4v7s��.]��@8�ҽѷ�C���P��Wi��=�X����j������v��Gu��g b	g�û<�E�p%���|r�K���O������[��*N_��-N7qZ��~NOrz��`n=9���0N�r:��\Ns���8}��M��r��ӓ�^�4�^ON�s:�ӱ���4��Ŝ���N��t������$�9
���^�֎���_�ei��p��?|1����[�_-��/{�t}ۡ@��%~�Kx
���~�:�o���\���%������ܫ�x��w|TE���		�",�Hр��z��R�"E#IH6ɒ�lI�.�����1b��A1B�[��G#X6��ޙs�MfN���~��?~�~�ٜ�=w�3g�̝;�,�o�8??��_ӽ&.E�ĵ��L`���nj������֝���ډ�ҧ��˯kȎ�i��M���i�ZM�u�x]�:���uݤO��I�«�(CS�gW���������qy��mڙ�O���u
����E!�k?>ri��i�i���{�_u�V!�M�ē�̖s��[�M����T�eb��4�u�S��ܰ���ҵ��]�"J&S%��-�6����bj�Z��bÎ�M!�fS~�ɔ3�eG��9 d�c+^ZֱKY����6ͱ���4�ϟ��<�dz♵L˖7i�0�-35�<����
ه%(8��3��:5`������Ҳema\t�щm�wn��߲��-�����z��anm����oyK��b�dn<��4����-M�V�Ҁ�`s@�kD�XK�9�e���.bmh*l���*Ȓ�b:k�@�9���������lnl������(!]�W�7��捄��k�64��;.�dz�+"�d��p�b�mV�z�9��%�p���)��ڗ�L�����G�=Xֵ�����ϯaE�Q��h����f�����/��J@@#&-Z��-;ne�m������x[h�Յ}veGwv�Ŏ���͎����4��1���c(;��c;�e�Hv�f�v�e�x,��>'�c2;"�1
;�f�uv��Ӓ�?;�#���є����lk�ن��q+;��q;:���	a�w��;��#�=�ѓ���l����ˎ0d��� v�s�&e�0v�ˎ��Îq�ȎI�̎)�����~���c&�Y��Q�;�}F��1�s.��>m�Hd�<v$#w�O';\�HgG;�c!;�c	;��XΎlv���V�ϵ�x���x�ر�ϱ�yv���ٱ�/�u���"v�Ύ-�x�o⹷�g1;v����ر��c;��0;���#v|̎r����%��
�~��B���{.���t��kA-�_��=/q��[[��-|�Ŷ��&o��0��v���6�K:��L���m?��?l�<�c]Y_�|��+C/�?�䤝�/tݺ޿ō���B?;p,����9�$�U���?���ޟ/n���Ϯ���鳏�4�{q�{Nl�ʓE���<��c�ow�ù�s�ON]�h�-���P`EV��{��m���]�&?3�p�]=g���{�
�^4�Aށs{��7�f�o׎w�{6�u����rē�~X�{���1?��{~���Ϭ�ծdQ��C;_�b�﫶=�d��k3wm���o]�/*��=�`�)͇u�����>+<8s��=;B�����鲰O,]����o��=���[���|௾~�.�����^5��=�Ф�C.&|z����1��nKF7�/S�o����cw�����{��5}�u���Cw�y��/�����[7�?~y���������7���m���ͦ�{6n��'�^��=���e�$|v˙O�\�d�/3n�Oȩ��?u�튯G��Gƛ��*nF�߷|����>�i�N�}=�ݣ=nlL��&��[����eM���[���.��U�w�:?��Y�/�;��i�����Ѧ�|�O3,���;�謉׷�9�����_���eˋ��}yP��V�Sz
��rs+�����}���c�c]�7�~�m[�oyy�S7�w����$��KO]���u���G'$���b{8 �{�}u�.�,�o{�[�WV_{�݉>t�s�1������6oj�ckg�]����!;��1���{sM�=������U����-�3�����z��#�k��.�Oټ"��]�C"��eO��4��;w���;t�g��i��'���]+��Ցj��mj~ @�Wܡ�۫���jkPϾc�|�A�׻�y��j>;\�ݩ����[���I�+F����j���̵+�ݙZ*�۠���y'?52h�+�j~ޠ�w��x��?lP�=��|�A<�`�^�74(� ~�Sep_{O5Oh�����05�g���vU��k�rW?5om?3C�
����Z���v0������q��K�h|��~;���G��f����
��]f�s��-5����j����R=ǎָ��|��C���x�n�����������m�?A�Ÿ/dc���40�y-�?C�ow,�nX�Sr��c}.�I��@��j��/�R�A?/��J=��z���s�<@�i`����Kㅸa&\��P�_����i6�����#��z:k|�!�
�o�Mk��;`|>����o_b?
����f�3��r�]����'�;��%]�7�r�i�G!��!�!�p&�'���m���ƭe��3�u{�����#П{�<f��|�V�7���q^�Nη�c���]�%��>X���Z������ho��c�����Un��Ѯ���|�Jk�3�5�A�cد��������/��n�
��}�����|�����4E'��.�?�~�x�{c��d����4O�W۰���|���o
E��,�u�������%'�!�SQ����Կ.��� 9n?���I׿C��ǈ�rR�uK�i�Ɵ��9�������w�<�/ƼQI�_���G��&�=2恰7�r�����R>���9��+w����2}��y[n��<�;9_U��i,��%c�X�yc���+����B��|R��?�����sh4>�V/�ǋ��K5�U�w���������8�D��chW�xٮ�X��W5�@,�c�sD�<������[?�G���G�x�>�G��7�-�Uo�]��~��0N_/����]�<�
�w���x,Η,d<��)�y�P}<��f:*�SY����1�	��y�Y�3?k��yD���s�>.�@�E��@���W������/��5����1T�o��q��]y�
'ky�?���~Inߵz���)A�?�b?m���C������ܾǰ�Ӹ���B|��n+��՘����_#?���M�4
۫|����>_m��,?�=���9�¸��"����|�C��Ѯ�#2��O�z�����qIjP�^������|��������{Ļr<_�<\>N�K^l߈����j/�9Tηb����i#�9���<m����KWlo9/��R/�g��zE1N��b���<DSl���[o2N=����;2�G?����+�Q�de7a9=���`}\r�^�R��8NM��?_��cG�G��>��g�y~�>�V�s�'X�",�r�<����;����zܒ��F_����_�o��X����W�s���ӟ�1?X���9{q�mi$Ϸ�����ߵ�y]y����B�k4�y��8�(^!�7��;d��;�?���k��@���SI�ϓ�[�D^���{�2y�x!���Z+�v�����r>�ya��N��́��1~Vb�+l��?�u ,�{�\�S��o�����s.���]�]�"�&�M���_�?���C"&��3a{����q=hv�ԟ�����n������/����[��G8o��ػ??m�����w=�`��u��?���߳��~�O�����B�n��)��_��<�O���kS[y��a��$y�{�=By<��N4�?���-�s1�/K�ܿ������y�����S�ûp����&�����F�G^&��������{1����sl���$n��xZm��Ӧ�_Ӵ��㯞g6����q^�A�χ'a�r����%h�q2��C���~q�/��y��O�O',����;��0�
1��yŽX��EZ���o�o�G��"����Ld�i	��{��߾��E�x�Go����܀�Y��? ��a�>b �]����ј����}�U�0Y?�Kѻ����z~���"���9���zl�2y��1|/�?\���c�<�3���2�"T��d>������*}��F+��j�o���q���H�����^�ii�!�)ǭr�z�]�=5������,~E~���:@)YH��]�췟�u�!�����<߶���@n���'�r:p�&��1�˿��|���O>���k!c�����^�^��~dA�g%�w^\~y?}��vi�+�7l�ܾ�ݫ���ү�8�<���㩙��>�����w���_�_���x}�n��9؏L�X�3��yf!�[e;9�>A��a��g����G�9}(�k�.��������xߐ���nџ_�zi#�3�$����"H���)�>��r���#'�p]����7���5�^>��D@?��&���n��{�ϧ���/�ۋ�g��
N��!���r�멼�,�Q*&��^�Z�@m1�뼄��'w�⨨]��9�v��Θ�oj�bg��N9mn��#CTF�3;��䴴$ևn���(�INN�
`�JKN�	�	+���|O�3��z����Ipj��vW��ΎI���f�3���`=4�`S��b�1���N��%8h��d����<[B�3�����<N�&�#=&�CRDFjLJ�iW�iZ���ygϸ�`Ϣ�
-�ի�枔�gV=e���R�����46��I���U�\���?3Kt�@cy��Wz�����c�x�i	,"\����U���ee��$䔴t!ŧ����Y|	lv��ʆ �+*��b6�r��7��qBOJ�%; /�9إ�<$'�pM.zTI�'$m���L ������Y�e���S G�;Qg,A������8�>˫�i]_�к�c�Yc
�0@��q�H[�=S�o���l�,AjÖ��|�S�)��T�Kl�#L^R�X���1�9�7Qԣ�ޒ��50�V��~l�Z�O��Nڒc.�>�S��:�-Na����T��2R!���b����+�yh�$�i<�k�$	׿����Wıl��;o*�=9�	(�(Hv>ֳ��AN�j��\î������<6�v����5;W���[[H�;����Sս�3'�q���ޝ�mιi.e7�Gwi�6�V`��I�L�u�.Y�
�go�����i��;
�;�邖x���q޳j�;���Rnʻ�ͮ�j�k�R�t�C����RI�-�æ-1�	77E�ȕ�<EH�)
�|%�0��i�ں��z�
��bI<����
�0/v���:n�����m���M/B₫Ȟ�zK�7�����B�O"Ĥ��z�H��O�;����(���M�q]ċX؊)���'��k��d��.��xF�:�9r���TQ}y�Y��K�B���ؕ����:k���θl�t��������I������ʵ*&��e²���-�A�3ut�v���;-�
�h>�Nc>¥s��1�$�op�pC�Um
��R�-
�����q�m�[�bb�]_���giN�I� ��z�q�Y��I�1�=���_�οtÞc�q���q��I�1�47�37�27�1��&�A�)���h����(���%j>�5T��Kq��1�m�ng{����$V�ܭ,��aC�-�f\W}n������G22$���&.�M�ӟ3�_�2�L1m��	��ӂ! �ڬ�$>��;��F�W�^ጼ�V���u��ɴ�,��O��n�gr�d����l�s�X�I��6f��G�_u�0w濬�<]����)�����cq�(>IM�^Q@��f6�esVg�;GqG<7���a�+:i�I|KJ_,�W�|�*���T�����*LL+��u�[�/�^Lg�������	��>����u��
�k�����ψם����+��������N��:6��J2������@�	U�������:��������������g���e��1����������sYk�Mߣ�� ӯ({���^���6.�����
��M���|�]�0�#�[	�s���#	�.K㉄Ǣ~&��ȋ_y��K_��e�/G^A��A�����C	y8����i�A���o�rry�/���_A����#�-�5����g��w!&��u��>��A�D�?���/u�~B��M�`�~
�K���$��?�7��$<y
��D�#������cd���3�P¯!'�U/�?ὑG>y"�3�g�<�p���#/"�-�%��G^F���+�F�#< �[
�w�?��#����/�����u���7��C	�y8�w!����?�P?����3	��<��y�_����ǐ���9���~&�j�3�/�~�M�#&|���g�:~�	��םo4 �L�}���d�6�:^�o�~&�D�3������¿@^A�	��6�z`�M����e~R�?��8'�)�K8ᝐ[	CI�H䉄OC�Ix��S��y�O"/!�U�e�������}�W"�!�Z���u~¯��$��>$|�>'���fnF�����~;��
��|�o�_M�D\0�#�������C������'�𧱜pZ�\�_��'c;~G�_���~�<�|����/���_ńg�~	ዣ��^��������w��$��[�X~h�z�E8�>Է$��cDn���0I�O#��/���$��E����8I=n��|�9I����^�_���RM��k���$�<���d��V½����7��M����ޗ�I���d�~�|��~A�zK�P���^�WQ���^S
y�1����'Lx/�IQ�	#|4ꇧ���X	���)j{sw�~~���B��P�(E�O���B�/MQ�)'|'�W��������S��mL�2?��W�z�M0��OB��};a�G�~x�zߎ��ԏHU��&�%�7��>�3i��{	�@�Ox֧ U�/�������T��Ex
�W���4�Q?(M�_(��gP?$� �^��?� �����4�>�L«�|o�z?I>�c��/#܇����$�����ߛ��&�š�ge&��;���B	��a��)�3P��P�㊤�~�C�_�A�b��t�����������oA�"�z?X	�{Q�ԡ�'VNx�W8���|��G�j�z_�i��ރ�q�z�Y0�Q?d�z�*��~�>_�?�J�9��|���h��Q?q�z?[&��>���u�|£P�`�z�[�Y�_<_�/�����_6_�_����Q�r�z]5�Q�f�z]����Q��T�!��C����H��P�Nu~�~��8�����a�_�T��b�A��z�`��_n`o���cG}�Kmoᯢ~�K��0����oq��F�=�G����	����K�o�K�9�˥�X@x_�/t��
�g �\�^�&��W
'�qԷd� �e�wd� ����V����OQ�0[�=�b�O�~I���/e�_A��l��b*	o}��l��ej�����˘	7��<�B��J�h,?l��{7�ñ|�
��]$�s������8_���+����!���_a0_"�
<Hl_�7�W�M-�b������E��o.p��[<G�f1~�R�o%ƕ�[�q%�6b\	���K~��K�A�e�(Ƨ�;��)�����b|
<D���,��w��:~����U�f�wx�����/���x���!ƿ�{��/��b�����+ƿ���_�ab�����/ƿ���/p�_!�� 1�>X���_��b��1�>T���_�����1�~��)ƿ�-b�|��#ƿ�Ǌ񿾎�'ƿ�ǉ�/��b��*ƿ�'��/��b��~1�>I��? ƿ�'��/�)b�<B��?(ƿ����/�ib�|���!ƿ��_���/�H1�����)ƿ�g��/�G���l1�>G��G��/�h1�#ƿ���/�X1�'���:n�_��b�<A��'��/p���'ƿ����x��O�_�ib��!ƿ���/p��w��/p�����/�t1��!ƿ�3��x��_ ƿ���/�Eb�|��_*ƿ��b�|��_.ƿ�����
1��R����c_-ƿ�s��x��_#ƿ�����:1����\����/�'���z1��A��o�_�O��/�����b��@��?#ƿ�7��/�g���sb��y1��1����/�_�/��/��b��%1����E���*ƿ�_���:^$ƿ�_�_�[���b�|��S���%ƿ���_��b�|���.ƿ���_���/�b��}1�^"ƿ�?�_�;���.1��[��(ƿ����/�b��T����_�����1�~P���_�����1�~T�����11�����X��"ƿ�?�_����/�r1����?.ƿ���_�_��/�����b��1�^!ƿ���_�'����b���b��1������_�?��/�b�����Y���"ƿ��_࿉�/p����_�������_�g���91�~^��_�_��b��w1�~Q��_�_���/��b��/1�^#ƿ����/�b�����[���#ƿ����/�b��$�W	�O���x���T�/xC�����+$�J�7�O�M��y�7x������֫$���f�
��|����`?��<��4����+��\��A>�����\���|�˱`?��������6��m\��A������\N�A��e;��z.��A^��$���\N�A^���d'�S�~��q9
��\^	����˫�~��py5��f.�� o�r.��z.��A^��<���\^�������~��\~�y��/C�s9�y&�� �A����`?����y4�7�� ��`?�����rO.?
���\����O�� 7��w`?��\��������A����~�Os�G��wh.W�� ���O`?�ǹ|���O�� ����`?�;����6.�
����˿�� o��y���~��s�4��.��A^��`?��|�����`?��|쯆��r5��L.���<���~�'r���h.���<���� ���e��\����k�~��s�
�r+._�An��k`?��\���j���A����`�v�������ϡ�9?���&��f]v6ߏ��8k^@7��f�]�5��~���,��,u7�����&�-���-�u�����:{��m�8�6p�;�7��D벃��Y����C{E��+�AVa�@�1�ڣƚ��5��yz[k^��xmY�����-�`O��U��"��-��AM�����]o`ͭ�����~~��
{k��]O��8��n=wY�G�f�"sq7���̸�+�H��2��>XȀߥ��y��O�H��i���՛ݿ޿�y�|6�oX��F
��5�_���KYs�w
������t��[��?��W�gbw;�,ʮ��~)����Zsˬ������������{źnQ��zu�]�ﰨkH�Pw�P����J�4W0O`Ws�X��Ϟ � +n\u�sm{�^�>4��X^��+7�'��~q��W�}���S�ܫ��#Ap��5o�b��@p��;��u�1j:��?�X�T_�7���w�܍r�i��!��_��;�=��뺘�#�}AY~<�b��3{�O����@6�d��o&乙�+/�;����~���߸1�k]�=�Ѫ$�t�=�v�ׯ��G��=�EX)�Y)�n�^��3�s��׈����x��ɷ��M�f0S���;�`a4!��{�5����%��}~�r��;����CA���a���e�cM'�^����ʚ} h�=�<��.�j�s�,k���`��Qs �Y���������o�S�9��ܙÚ�����������S�/������/����S��	�D5�]��CP?ױ:���'��HF���,^�i�ҿY��.8+�wӥ�5���-����Y�������!�׺��״+�C���]p�9pt�3��o��sG�Ϧ��3?'����Q��Έ�z������M����J��=�{.�������ծ״ҙ�,F�?�N�!��r@���Ӳ��_�7������W���? v
6�K���<������v���\6�8�Z��q_�un��}���.�p�^��]�<��&���ső�5�F��/�/�b�u��db��{��֣\�/c@���K�}
�~pRn�/k$w�߲?����ega{������<Q�\ ���=����v�?� �����V�Vu���V����?��m�������2;�f�̄�{����mY}�^{���-q�1;�}�y��[�U�f��@
�M���ݧ�a�
֣k�YHP��O�[b���u�젌w'�ϋZy�s�Ӓg	ZY깽�e^���h]<�U��g];�s��ݙ�Z��2�u����B����kG����uN�^+߫�^~��׈����H{��Ij�v���S����Tk�2i�o�^��%�Y-�WCV5�Q�^�
Y״&��"�j�
[�`��-���r��y{���b�hlh4��ǒ��&��xwf�)�=`�����{��������γ�����kUL�=), ��H���:$�������݈o�}S�w>��P�@s�n:͇y�c̈́���U�ԫ(��h�	޵ ��O�? ��'�3#0���z��K�#�|��Q�پ�(�����ۑ����z�`֑���r��N�巰w@�9F:�-����`�\�Qa�Id��
�b}F���u��1i\����b��p/� a����<4���{vK�f�Bq_hO�����p3��TA�T�
?�K�{�8�e�4�z��R��s#p��J���v�'
#h�V�I,G>s�Jx�k��4�ܴ�\�ɾf[>,4�H�f����%b��u"b���6ޡ���NL����Q�
g܀mEo��5~�|A�#�Hr�'c ��z

����i���
��C�ؠ���סt�7��%��Z9o���ț�qM���:��Ohe}ɕĶ�&��,��x���9����N�'��ܙ�m2@H#}���/7�k�6���k��9�'�p%bb��_���r�L����#8�Љ�[<^�W��30z٧��w��K[c� ����D~�Oim-`V;��i�������Gkl �qV��A+W��3/�����A
�3���[��~�$�t��LL�1�R�����:q�l۲�XLi���۝��Jvg�.CO��7�Ed^����-1>��;�>ȿ��Bh����f��?s�P!0'^��3�7�y[��&�LQ��,�O����}!��B;~
��y�i@�q��  �k��a7����ߧ_�w�$���'X��*1�uA�Wٗ���Kb=�Kb=�6]Ĳ�t���E��{0뱏n&��t����E
[zI,V}sI,@��>U�?�n�����1���;ky�V�|�S+.8a��Hg*y!0>�.��8���'��N!Q��2^'�x=�5Ա�d���7���<JgsOH��v�c������]-JhsNإ{8�+�Jy����!xj�!H��7)L��Ѷ�D��`��9iͳ��&��H6��	Gٔ�۫��`զ+�&Y\�Y?��ߑ|ZSW�R�1�]s ��C��^('b��#f���8�1u�":\0F�{�{����A�t�sRR���F�:+���M垞�����r7�+R;>�zNd\��V�^��
'��~�w�7�ٔ��xc�5d+ܮ�?�q��Rl)�YO�<s:$�!��R�ү=�e>"�B�(�n�T_��������M;�y��-u�b������aW"���������>�"l��z���=j��qs	�
�G~.���� @��1�ƿ���[Iw�d��n�"�d�3�
+޿�&\Ͳ�k���S7��h�k���[f*� �q�z"7lYcح��6a�q���Id�ٞ��1���,xv����dq�Gk�����.�ѷXˁ�Q7Vb$�����V��ƒ�U��X$�*�a��/��a�\�Y�#�/��\��;i�ͦ�G��5�_����=d7<D���â)=�=��ZR�Xq���s�1�^<��_�Ra�{�ԟ��,�o*+����4n���3� ��V�ޙmkw���(�_LOD{�
U�T��`���\�|�gj\�N�^�D̠��u>>���]>����Z'�a�����8��Iq��(ځ���"�c����w��-��}�\͞CeK�\��+���p���[l�b���D�S��8%��f2Yi����̌���z�]j�"�^�rD[p1sS��.�d�)��sp������ �ʬ�12u�QyW�c������.�+��GAlY\�q�ռ��;l1v��,E �b���l�F�Q
u�N)0����o8��s��7��;�(��0��i��6f:�9�������3j�ϙr���A­뛉}e#2���2��i��M���
l
��{��Ƹ�j}�b.L�-g}�gw��`�s}c��(�RA��X�Cʽ���;:g�y��i5�����k~��>��h�2��]�_ ���V���.���9���>ۿ����`<���Lp��7��Z���z�[�-��,����/�%�I}�>�+��*�[��q���ً���l���_�����uP�(xӒ�:D�{�^b��D�Uu�.�
{��Y���Ou���|8���z���/�V[�-(&Y7Y�=|e"~k_��w`�C��gP����������!)o����W��jm������]?:�-�>����g���Yב�%��.�%����zEr�2M�K����K�L9m��	��.�����9aD���2�F��}�m#<�lm !g�NE��W��8�}�h[�QJb�<g";W�OSSX��^20FZx�5�~G�QX���þĨf�K��/B6*uwkuҫ$|deY;�c|E�]�������A�m��!c]o����h��F�t�E-]1�y���
�O宙�!�+B�?��0�����:������x5ށ��%�'��+��u�mUBpk�b̔�9�����;�o��_�\���}H�YSo��ƽ����a���,��zf��Kw��(�E��d���hH)>s1�5��݃r;�J/��tr���E�ɍ5@@��PhU����B��!D�o��b�(����ڊD��SE��Q;������ي_C��`Y�(�RDv�(�۽�dA���L�si�U��7T�>�F���gx��4/<�߭��W�� J<���Z�9<�ޔ6�R�4i�&���f�͆xx�� 6��u�.���Jxh�U����>ڊx��3��1�C~r�	��a�fg<,�e��	#nKxh������C;
p��^,U ����|�|��ӧ+%�8Vj���$燕��W����r�� -ߠ̷��������
���.�$�a�m����O*T�^�
T~�
�`�����
�+���j��f��� 7��MK�/��ԓ�L4]���E4�rT�f�~��Z�M7�5W�%d�n\o���R\�e�	/�%^ ����%��
��P�K����Y���Šܢ�_9Gg�W|����}A����|��|� r�"ޛW⚳?(qME�u�E
�T�H3{�5��ODsi�h��f����Fԣ�GK���Z�{��Th�T�������Ϛ��p�����r�� �ը/)~G���U���6��種�_�������,��?��C�7
��?H��W	4�+������+�闥(�k��ߛ��Ӕ��|� �H��|e	j2NU��b����x(���	�w��c�o�P�`'N��6?	�:PȂ:�.��@�:jVl�6?	�O���F^�^e���_
p�-^ B7��q�%�D�ր�~��j�(wO8%|F� ��@��ה,|�
����1��DV7̶���͆~���	>S�S�<��g�A�4�?9��Ӿ�85qR�ԿM��'.�
O��?���?����i����ɉoRf��O��xe(������)�?9���G��B^���,՟4 ��L"�x/���7��/'��OF�R��;��jD8	�M�o�d�,�~����Β��[xL���l���s%�\��@�u�(OV�f�+�R�
�	��~�?i���OBf9��J�*x>8(���?���1�'��2g��O��ƱX:�򿉐����?�7���D�trf3d�gJ/K����t͟<���!:p"��B�º�z�?���ɟ���:���O��~��OMr�'Zj~�em域���l�?X��y��2]�W{R>��L���䗊@|�P��d�Wq[.��O��5��
��Ҝ�[	�.�{�I�ފ�r�'e T19, typename T20,
    typename T21, typename T22, typename T23, typename T24>
struct Types24 {
  typedef T1 Head;
  typedef Types23<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25>
struct Types25 {
  typedef T1 Head;
  typedef Types24<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26>
struct Types26 {
  typedef T1 Head;
  typedef Types25<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27>
struct Types27 {
  typedef T1 Head;
  typedef Types26<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28>
struct Types28 {
  typedef T1 Head;
  typedef Types27<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29>
struct Types29 {
  typedef T1 Head;
  typedef Types28<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
      T29> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30>
struct Types30 {
  typedef T1 Head;
  typedef Types29<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31>
struct Types31 {
  typedef T1 Head;
  typedef Types30<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32>
struct Types32 {
  typedef T1 Head;
  typedef Types31<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33>
struct Types33 {
  typedef T1 Head;
  typedef Types32<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34>
struct Types34 {
  typedef T1 Head;
  typedef Types33<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35>
struct Types35 {
  typedef T1 Head;
  typedef Types34<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36>
struct Types36 {
  typedef T1 Head;
  typedef Types35<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37>
struct Types37 {
  typedef T1 Head;
  typedef Types36<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38>
struct Types38 {
  typedef T1 Head;
  typedef Types37<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39>
struct Types39 {
  typedef T1 Head;
  typedef Types38<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
struct Types40 {
  typedef T1 Head;
  typedef Types39<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
struct Types41 {
  typedef T1 Head;
  typedef Types40<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
struct Types42 {
  typedef T1 Head;
  typedef Types41<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43>
struct Types43 {
  typedef T1 Head;
  typedef Types42<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42,
      T43> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44>
struct Types44 {
  typedef T1 Head;
  typedef Types43<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
      T44> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45>
struct Types45 {
  typedef T1 Head;
  typedef Types44<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
      T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
      T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
      T44, T45> Tail;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename
�%`:f	����ҷq����ωu {�O���4��+���s
}ם��wω���x؅�\�K�;+So���?ki�	ȫD�ٛ�J��'qZ�q&�b����
��yA@��Z�9/4����-��������D�?��̬o_%7�;~BԽ��s�
���VV�_��tN۾��D�~;�m�On_5�����QX"��������`�0�.���b%kiP�Q �<�J� �֜B��p�'�4r1 +�V�4�_�y�K�>��4��|�4�'�I�3q��<e��Z�X��vÃ���=RF���=����Ek�Bk�Skk���Z������W�@�?q����*Z���O�$���U?��S��Y1Jj��!q��L?	�R��"R��hpK���!��yC���(�Jo�\z[u�J�+W)=�5Ք��I}�!��	,=
J����7B%9�Q{;��5�����f�8`X�]D���E	���������;t��s6�^���e�ߤ����qTt <��n�����Rթ;�u�� W(�"��4��N͘}��
�jq�\�Q�o�F�pQt��{�q�l�z'���
`�z	U�g&*�H� ��F�I�M�B�Eݲ���6�W��
��Y����P)'��lګ���7��s��VPJY*%ݩ��;���T�H(%A-��o�
M)���ǰ�6i���� ����\t�f����)�(/�����l-�.���&�ͅ�d5K�ױ���S��
{[�ƛZ
��}X�|����H�@[�S[��%�-��aWҨ�m�2���e�M����1��Ge���ˈ�2��2FRCIJo"�L�,��4V�8yz�>��F�o�Iu�
�%Y��]a���)���#��^��������7�돣�k�����ֿ<��W��������������{i�;����k�����ֿ��+����#������t���P7��U��gx���d���]j�:�����/��ڳ����������l�ǰ�/���2��w����w���-Q��?M���$�7[|7*o��Ha�;��N#{Դ����&6���?���o��4LK4a��eG?�F
w} �)݆N�����و</Ky?:t�u��w�\�˅/��Cě��2�	&����A�[��e�O n�w�yQ�S���[n�O85�co��!�����y��%[h&`=�m)1���v7��;�+��d7��$_�X�oƹ��<�3#����~���G�v
����X�f2��`^������<<NT����P����0#re
��d�TGe�#<Їw�t{��̦��6��)�+����xRy��B��Opq٩p�6�kr^��&�y�tK%����\A$6�Ͻ����
�|�,]g3���I�:�M��o�u�}��-�VZ�y�v��܀4�Q/^4^z�֌��)��
7C�?��:�Ί�)��~��4�T�����.�o�%"�s�q�W
+ċ�OS����F�
3;|wV�AD��
3��i@#�z�P�#�~db���2(�w,��q�۟g�f�Qr����X���/��j�m�����[�?bZ�~��ϣ�dh�}-��b_�9�in������o��>���~^���~@�m�o�}wӗ�|����ڿS�E��#ڏ:E�Ɏ|��b!��,�ޙ����H��/g�!.���/=E���[:�������x��Ot��=�
����������Y����ۮ�9$T�8(��F��o�;��V������f��۬�����v����%'��I违���]���Ng��薪�����7�o���$��5�����[��R��5Z����M��ɓ�[����O�o����c/'�"�7��z��o���6U�}O���T#��q�{��͝�[���t�o�V�m��
�i4\
��"�g6#K��t��B�c�6(��X�u9l��C%��j��#7���B̀�n��Z�9�X���#��T)�	�x�,��PJ����Y�m�RZH��s�)�|����ѾE+�{�|��������]����B>��s�x��eH� ^;�J,�T�L܄tݜ����?4t
��ӿ�{M�W}��GB��?>t���v�â3�|�^{$���EHã�8
� �6��:S������h-��@Hvs�0(Q5NZ,�#��w��b�M�f��`	�,[&�
ڐ�g�~����~(���CSa�Pؚ���7���	���F?���臍��~����#j�����PD�����_���i�\��t�)O�
Y�Ы�,�p����y:z���3�./T��d�?Tؑ�v�{z�$�v�@;�sC/�E
��/Bz}_\�5��	��<gz����S�Ϫ>m����{�I�����!W��d�|��\��3�%����J��}G�5Wīu�t���2�d�,PퟅH?K1A��3��X*�(�����T�+�_����DC�����;z��J%��F�t�t�,z�k8���+
���G�e�t�Xۃ�8�����Y���I��f�q^�>���ʣ+&�-�4eW��de:��Zo���/8rپ��s�����"����:`�m�>�n)�z�ҋ�R�8����y69�3��80�v|��ߑ�K>��s�o�T�?Sͧ�dG��WE�qcu�V�ȟyO���HR�s�go|�z"�׋�?L�%�p@�>�]<��:�A���;�����œ=�%�ܖ��1�^xr����6�i򕌁O��'�?vM�c�U�ns�%vaV��U�;+�}_�I���d$�G4���|百o|N�	�����sG��}~��o��v���}7GK��d��9G��w�L�O���7�B<�
5�N�;���L����x�B�_��T �﹨���<�{�g4�J@)3�?��3u���zߜ��>�����L�e?h�yޏ2�M����;U��f�����Ǒ#��5�_�9_�>�=���֜\�}����o�<d��bͶ�x��8����d��g��8Ǚ�^����8��w�s�e2������}�}M�����(b+�h�{��a�Ї��AC[L�������*���"�_~|-٪5_�����fj��L���i���1�fa5�VY����͍`<8�	|��Ȓs���L^6��Ώyag���� mߚ+��9��g��$��L�9C	_7K�}���ZL��ar�Őj�,% �7;�E��Q�oV�D��Th*�5��:���A؉�x�����S%95r���,�o�x��ȱ7Ɉp�2m�fN���%��a�)�Y�~�H�ܷ��$f�L�im�<�Bv�����~�!*���G�n,�)�+$�i�/7��5iQ�r��t��{�}�amC4�c1�%���������j|KScam������1<Zz����ߥ��k���}�b.��pS;c�4C�[cE�1�oLN�=�HJ���C���q6<�희;����(�!�Gu����ߓ�zz*XX�kS��Z|� |B)��̧��=[A�ؼD�+�$�~�!������;�n�
���_V��&~4	� ��i�������n��I9
�^Ys�,�
����3R�}5���Aaբ��1�ۍp��jc
��3��3��ڿ���&;�:$1�hNL7�Ա'�Ї�T��
}۱\<�����3��+�ȍl����єy'��N��z�����Q�4-��-(�����cKf�&0P�.����:�v�rw�ye��>�
����,�ޟ�^Hܟ��ܟ�N����������q��瞣AeJ(D��>���s=��?����Pn�L��W��d���7i�� G�빇13��Cg�3:N7�BB_/���$e}��ջq�f�b� b49߆s��PA�BLթ4f-!q��כ��yQ��$T�k����L�#��}8��U��(�����\7�H+���ӱÑ���T�4Mɼ�Л,L�&q�b_�%�|Us"
�TVs�
6�"n5��j2�K��K+��`
�Ѕ��1V��ȡ�
���?=xk;-�������������j����W���'�1v�[�����d��O��~IB#�7Yz+F�o�-��XMlY�	rlYK^�dBom�N�{S$�4�
��
��'��m��\��(���i"�������;���Ǚ`G'qswc��$�u�mI��*����kr\��ȁ	ā��/�o�t�Y��g-���ߊxtC����zx��>���r~�=�_ڷ��'�[ݽ�w�%�$�}�$�����	�����[C���t��I>U}��s����x?��{O��YEp׻�#�1�a:�
 �>\G���hi��c�����SY=��F���@=��0��uK�$eݲ�N��F�S����%�Q�Y�l���������ʿ���ߕ�_�L�9aل��-����ǫ�;�j0�?ʯ�|����c׳U�Yu
~�[ j�W�G�䣙�U�z�㫆��:���Z[{�����x��b,��-yqWi)FJ��O���I�nu9�-���g3����c£U<�m%�|~��_���|��ɯ^̕�+�g#%^z������f��� =S,_�U �f��F��q�vt�g�.��5-��V��P�E�?M�<J��C��su�\G~~�.�W���T�kR~!]~I5ߋ�����Ô|���]�Q��S�*� V�8?��bS��d��i��sd~��+sT~-��'�*�3�s�&L*O(�������^[y���r~{��P�uO8�䟀������Bɯ
l���u��)s��=XX����\B%�
	�V|m ����`�Gj��t�Qh�߂�q?�Z;��h�{H�Ư��	��e^t���m�}�>u�I]���PקDR�'��v}E$u�����4]���V�?�������R�ϙ�kq� ����CУx�/٣X�S��_��ޓ?��g�?�8��	�H(�9�}^⏃�{���V�J�Ϣh<���}^�d�����}i��y���6~�~�$�TБ+�_ү(�e��/Szk�����~�����Z� �����]>P��^��AS�T���Z���&���|�Np���|Ap5��V� 5�z Y�N�����<��U}��e����?ؙ*��3������u�W�_��~CS���2�2=���s��U�/�O�0�~��Ա�S�{Ї�f�4t`b�w|��켾��ԀeT ;8��ʶ�b�{ �w�v�{��+�'	��8�����sU�PNز~��@�AHg=G
�A����N�H��[����0�6���?\�M&�sQ��o1�Ȳ>���CM�MM1�i�����9����?3�
P�-N��]�K�C�?�_��)d���O��ɓ>}�]���Ww"@��D���*�9��� :h���u?9�`w9�G�����~���b?�����џ���Y)��Y������~��9=i����2���꟠~jq��邢��_�Ow���[�O�H?�7r�����r�~�z��SE.�(�k�ͽ��Vfٟ荟�ުV�O@o�{�>_d����,�>��OE�<���������jj�,a�t��+�U�ޤO��6sFՌ���_�+�П\���P�������M'ā�H�G�!!.��"�?�!!�Q������>-��V@1`w���<���>k4���ݟ��zX��t������>���G����}T���>
ꪳ���)�)�~V����D��u��kh�����l ٻ����U#iaoe���2�����]���g��l��f��U�Q��n$��r��ܼ����'J��ga<'�U��4��uՌ��n�g���{�3B�v��8P�F8
��
�����I$)7GQ�SjI,��$m4$I����3�����_�|����+{����S�IY?\��N?��e�H�i��J=��F8��XN�~uR��O�~����tu�������;����CH7Hu�:��>]�S�����㝮��c�	u�/=�������2��?��זH�c���}�b3?<A��t{1�#O��x��o�;F}����Aݤс���P��߫���P��55���4R}����{�0��Y���ح�����;���j�������M{]ף�S�����v}{u}cu�����_��X�Ƴ��lW��#?�[���<Bt�����]�V
��B�<�,dK��S��]��P�é��P~L����x����co�����4>
�%쨢_*%��s;���8��a5%�r���]O4R�?tt����kX^[�k����Yo,���
�5�L
�G�������-���IP�������g�^���������!��^e"I���(^�HR���I�;����Cz�lPa}��D:7?��Y{U����Y8�B��C�:���^�a�pTި��]X�m֟��菢m��H���Qw>R��7!}�8�����=�"���C���h'k��>�u��B�H=qT�a-b0(C4	�:��5I7Q>�H�K��)�
�u!�n4Q�t��V�G�p]
�p����#6��ދZ���&�w�����oT�#`#��]��/������C���z6MWG��]E�����7�ꀏ�Q��po$�mӜnp)-��I�o*��ӷh�ZI �#��(�˷z��*pA �̻�&�E�>T��iZgңhi'[�`����1!�ׄ/*u|�BC
��z�tk�@�&���g�´�:�=k����2�֌�VW�̃�XK�_ ���C	���D�*0^�L%�J\s�������UT�%B+Fh�L�5h�
pq �D��:̔O<I.��S9��.�//<����+
�;���2Eܿ+<��[w�n�zqZ���P�WX��6����`�}���۷k�ip�}�&��`�}�y�[ٿC���:x��J������>�.������l�뾝�k���_	p�3
�J`�}�ܿ�=�5%��e%��f�q	,+�a��mY	W�m�rU�?�ب���E�����˓9S;E�_ؤ��_X��׼Ts��V/�_�܏o�is����9F��摒���8���~<���.f��9�
�x�?Qa�)
����I�O>��ú����Y��?|�(a��gpF��N�-���i1����(�Q���g{�+��<m�d�y��s��y�+��TX
���T����?�O�a�Dp��s ����Y �ɛ�mI-�}�j�����H�%�o�R3-���?@���z���8F�@�hO{ c�Y�������
�����P��V⍅(#��ƅ�}U؋
;��@��M�8N���u���1��D�'\4�9���c�F�H�zŐ
�$�C�iS���p�
����L)�6�ׇ��X��?��h�ϸ��~j���|6��?(���Ԗ��S����S��J���������T��M��RdF�5fC�1/(?�y�i�t
M�-�y�d B�xH@��qH��.[���i]�*�ќh(�?�ќh�]A���~�,�
��j3Ҋ���D� ������7b$�F�_���_�t�&L6Fn� d+!͘�[�/��x��\�L�yE~�#>�E`DHn�Ň��m�I,��9����~�-�������W�͇��{�Y,��|�����UL·� �q$V ��/���I^"�Yϱς��ɳ&��]�u׭���9��œ��/�1�ދ����Б� ��H�ro�
gk#���X����Q�)M�?�̇��0���(�����!��=�5�/����A|C��6����P������l�O7�s"�Q|]|��ȕ8'�V��=K���BԞi%!�_]�".�ajwA� po������A?��H�c|�Q.���y���-^���ҡ��x��o`�6)�6���tx��l-�.*H8�Pе�HD�����v*�����3m���
�ז֚;�֫[�V�:8�.��^іM���x��X�:��Dʱ�$�Z��T�󌢗l.���� h��[��h*{	~�7p�
��F{�n��Z
=t��}�S?�N'X�G���s���]fKC��7�\�K�u����,�J-q���T}l�]�o? |��.?p�	͔ζ�a~��w���:��Ax�<KCx�'�ͨ|:}��2��,L�t���(��4��p;R�ɆFP<�����ke�����ݖ�8y#�Z�R]q�<�D'�a@��"� ����`����[�"�ș0�ڷ����]��Ǵ]YN��
j�nK�э"����Rm#]�@Ǭ���ch�4m.�z5}�bR�QV���}Q �
9�o遞�r<���:
=��T��( O��:z^
U�NK��u��szU
���s�{�5wC���i��I�oKu�~+�;�o^u�u~���@�ү�
Rփt�9�]�����bT�T������VUu�?��7(,}��(��������,R5��IQ�4�ZZ{���{�,�
~��v|��w�p��>¶a�
�=�ΪU���|��A�O*Q������-�,�6�
�t#)�AϬ�^'��G��k`�����ǋ���^�������^��z����v�zL��XF��;D���cV��x
��_���g;0�=�8��8��9NCe�g�;X\M���5�=1x0!\yY���ĝf�b���d�k�:8�X�~�^~�$�.����p5�س |^#���B+#�Z7y�f��Z6[�Ro��Vr4����6�L��9:_���'����)�ϧ*����:���b��r�;����}4X��w�'����_�]��������c��0|XM�Ы��h4��G��
N�1z��tç�r�IP,�Ћ��f_���_F	(ߺ�NP���nR���U�.���9����=w���N_W�VT��n���!؊ϠoW�9G���w{ 'Bψ�P��O������ڡ����K� ���Rn̿�u���A�M�P�vz��Cz� 5鬁7i���5��j�+b,�ؠ��FJ)�n�?ڞ.���CA�
*(�(F�X"�PP�("V�Q z^�%�{��hb/�F%�5Qc�mϳ�v��̼z��L�������nw���������9�^Qh���5�{�B�������(�ER}�(Db
��w�<D�\Aب�RQ^�YHf�KX���I-
NrD��m5�+$�K�3I� �@��{�a ������E���@�t�R�{�����J�>�8�Ao�op�iS��Y#I*Y������k\K�������	�s2�?��п�UCW��5q��T��)p7^����P��9��K���=k,Ix{�E�Ng2�1A�~���11̷J��Ȝ	���9�P���ҁc�����5t�`���ĳ<���]lB��WXf������b�Ǎ��6�!̗�R/aQ�2f�7q�������
�9^��"��_��3�&�g `�!�X�A��@>Ӫ:��)wN��{f��#��'HRڨIi�,��(���IR�5�0Ii,��F)�u�^��Gx����w����EԪ �T�?%
���N,�V�uɠ�*d̿^&�����a�Xw>L>��]`~c���Q�7࠹��"8 �4�@S`"o���;_Ѧ,߹�~iO-�P&|ݞ/4����[��^'��h ��{|�h�� e��/�͍j�Ls��)�y��Y�ų�~4�2`��;�����:�>@7�]���K?
0D�+���M>`�Q��#�va�?a?QN��qH���� �N��Q�I\s�8����$6�s��i�Yϕ����ϑ����\D�����%.O�D2����NdD��&�C��z�i%���g\�At��LVϹ�7g�c�l�?Y�^ݤ���k�~�Ee���Te�Q2��=���TZB</�8H�'�+(�D2�LxM2�ʕ�%G�'�AO$Ѕ�gj=T��D2`-���'��VR����JHNgFo���}O_{����d�O
��,A��r�Tְ�
FY�8|����դ����r�~!�А�b���[��y�2�6����ۘ��ۡ������ ����R�-7�[fZ��ȴNKɴ�����? W���,�6q?VQ����wտj��b��#m�R�ޱ�V}I������{םԓl�#Փ�!ҧ�p�~̻��F�B79.Y>��ޕG���~���x����$�<~�۬?L��u}�7������BG�+���;���4����0]:^�ڤ76�������8ԘMZ!׃���VĆ��g ���`nT� O>6�/�>�P\b�X58��Oy�P�s ��#j��������W��}���NMO?�MgTP�7�&�@����*м:�ICB��{Ir�z]U�����W������~	j����Yū�¢?�����ɵ��:�}����]�_/(����m�9���<9\>�X��z�K�45>��ca�.��H�Xag1@,D�{G�a"����'�[a�_Q,TX�;�� ��;������>_;A�p�1��@9���8G��	��f��{�\�#��H��������H'��B������A�i�(Ɠ�*�]��X��PJ�ܴ�$/
�P8P�%���/;ћ��H�j?ҙ�b% �_<Q;�����9Q�K����?�����]`��)
Ʈ"{>P><�	*̾H.<��Lf ��p��F�vE��,Y�ƺ�l�{>=�l��"p�]b}/��b/S_o�UI��w�����X�sòˊ���}W^tB��$��#%U����p�Y�9}���}G�/��~��o���*��`G�"���IV[�FI��SAIߍ�"}K��;�S�o�2����N�ۻ�D�!�վ�O�/�h2k���k�����(��M��eT�Zގ�ߕD�����o=������VA���"}˔���.�W���,���K}*��T������%fp���o����:�F���a���R7L,L�XcOu�^�\J@�Tp_��_�S��a��l�s���D�B
f�L�1kLwu�|CФ�l��6/���О��>ԉ��}�����ՙ�����R�j6=~/�N�p�{Գ���2�
�BӤtig�|���I	�����WD�=� ?��|| 	�R�ϓʄϤR�����P�����n$���
�j��)$��3�#|���,/� �@�'P§���2��5�5�Й��	�R�I�L�t�B�/�B��
����bk `S��-���'��u�������*��9���.��h��ݹ��~o,�Z���+!ڣ�qt1G�7xK���dtb�K��=X����ކ!��|��%�����Y:�~�ώXzӖA�B��=�;��e|���^�����_�����~���B�s��}����{���q��K�~���C�]Em��J��ή����/��=_��.��G�V��̾�����v�a��k�~�`�*�R��~�s������O�� �?���"/E��mnWyɊ?���X)��~��"�����(���/<A�/<��Km���B6���.�ޒ_���_���ڵ4�0n������*u�v�.���*��Ʉk�+�e
��|]�V>�A���|±�$��x��nWG)�����!��_0���]c�B��	w*J��[�(�|���|�/
S�`�zKT� �$��c�]�Y}��r~���V~�WVe~�&��Ds��GI��>N$Z}H� �e���/\�C�<�6�
�Z߅��=tH8TbM��k8�B2�z�\6����k�N[���d����무b�
Q\Ҭפ]^p����oj���
��/�0��X��o�*�i���V���0�=��[���#�?�?T9��V���jD�>�؜��a�o��/Y)[D�r[��3+��`V��4=D37z�eo��C�������̮�C;�Tr�=㽗]��^��s7��&���?ҏ� �q���m��0
�~��B>h�����C���p>JEa����*N��Ͼ��	���!>ʃE�[��w��M����U���dgyY�>���#_�����r�`Y6o��C����d�(���tB�	���@u$*�c��Ѓ�jn���Nq
�	���E$`��l۩Ʒ�Y^�B��v������n�f?�:0>pF�?Ο�8e?�,�:��.���{������%|�dAn���r�o��l���'�#�U���o�[N�m�߯�I� ��y@s��ɬ�7�d���%�g[S��z�S|g:ˣ�讄���r�|u�<��|�1%�V�!�i�8A���r��%g�����"ȳZ!� ��
;�#\L-���W��9��_q�o~c?�w����7�\+D[ؼ/����^�޷�ߧ���y ��o�%����:{�0�}���2Q�x_I��e��߽�@�����_���OC��M ����w_��s�5Y�	~,�_ �#�6��ߺ��2���Vs��6|����3�����_����A���6}�;���J�qr�{��qЋ���Aq��r�bKO�=�h�wH��
�ĸ���jpGI�Ľ����qm��ކe�q�����~�����g��"��Wi@�� �?�M�X�2�o;��8�?]����ц��\H�?��ۗe�ץ|���z��C�_����r��=�_Y��� ���'�����������o�!}E�+�C���g�����v��%	��?�.����i�߂�&��ևϙ�����*��Nס���7��߇���5��f0E��i���)��.Yl�v�6�u�����IG_t����NY�P�U����S���{H����fŘ�R��@c��wV���kx��R���yU8}�sU8}}��p0�rU������Ƌ;�f��,����7˒A��J�R�X;=ս��L�����R�g)!E��0��{V��z�_=���ge����\������b����*�C&7v�״�e�p$���+f�Ϡ�ya��x^U<�?\b�DH{8,{g���1�7�0$R˩bꦇ��\�&ܵ�!y͙�.�9���w��>��\Je|�됐f#��"�'��on�����V���`����7��1��>�^���>k�4{�1�n�f��8����o����3���ġ� A�_�*��G�&}!2)��y*3i����DdRX}&y���Ⴍb^�A`����g�%bZ�Kt{���`Z���~�"�$��]{#/FPҟ:���A��������SL�d�g���ֵ7��'��ٟ6XXˇ/s*��iw���E��r-k�|N%-�s���a<
� �s$�H��u�.�d�u	o6H��$Os���4�&D��������K	0�J�(1]&�]C̘�Z]$J~p����^��:�
�~ '�'$p��-󜺻À Sf��Fp=(Q�	�����9 �:�>�C}^��S�W��b΁,yO/��\���N���27`ƥ�o�t��Ս3u��!�E��w
!)>�%��J״�>��U,P�M���{�2&ͣ2c��
�J��+�/Ǆ��:C�Ѣ��鰢a��@���A�vπ���"���}����u�h]�cV�|@����3��Qƽ|P~#V��
�"}������`J��[���^��<��OY�<8���"~�d4x�Rf3�rT<�����.�:�)9�z���ࢁ�,���8e(���,��.����Q������l��C���t�2&G�}���R<��l�i���?y��Oc�S;̭��.�E<z�Y@��>Q��`aɎ2%��j�b5�
��1�[ιM���G�e�B�!�H
0d��|���o��8�Ӕ����I�(Z�F>�X���%���(��D>ū��{@��!'%>�;&��1>�zG|j�+�	����� =���_� ���
�Sp���?W�quE@�x���+�O��jB��FK��rN�|�>�[�h_�����*��z��V��R���S�F����3&���Uf��檜��R�D-L��d ���-���/L��h2�y��d���&�`2x�RO���)\�������auO��
����"UW���'"�3!�B`�n �[
�
e[�=�8,�
s�?W�S;�?�|�>�1��I�Z!�����c�dȩ�կB2w�������a�
W�����I\|���`�ax�t}�O�J>V�X�Eg�}[a!'���]ٙ���
P�1��_ �\���/@C��aށ�������[92a��`�[L��V)���r6-�_2��,�QG�϶���U��/..��CT�-�<�|
Z�1!؟l��e��H��@��V����B����0^W�HS�>�4ĕ�{�m?���!�fa���ȸ�R��9s�D�\�{�UH�pg4R�T�
_o�u*������a[��~������ug�_���Mk u.���/�!l��?\�h����&D������P�֝�0����,���0�<w���.AD�|�1�z�U�_�XiN��?j���[��L��`�80��z�P���i4}_�^!��ɣVE~�͇���zE�����?������۞���G���ƶn��a�2\�����y���܃���V��Q|q�u��ChK���&�x�u|�Cv����x�2Ჽ�.ۻ/���o�%{wӻP��7[{���x�C��o{{wQ���g��U���-��������k���l��� .�b
���b�m�%�������j�a|��hC;m?E��?�_����_���_��4���U|�=�����^H�-y����+-��wT�Ӂ�����y|q�Ch��Fa�Q�,k#n��s_<2�>���A������o�[i~�o#���Q���秩QE��
�_�٢��+f3�����U��g�P����É�P��>.��QS��7����Pwq
�C9����P�=��e�лg
8N�d�s�8��f4�� 3L�2���` v��fJ�5F��4=}�7,��"�� ù�����  ���ֹ�ي��f,��ӏ
�@k�K�5��*���wĸ|u��{c��%��B*�/�iP�_����@p�!JHB$�M(���������p�)��B��)�*��N�gH/s7���,��Ѓ<���S9�� >��
���"97Tu0',�iN,G�6�$���J�(�U�➠Y"�&v��0������?�4<�.�pίq�a�ۃ����|p>R������zJx���X�>{$|zG$�=��ylB-�`߾r(�*|��d�:ķT�wl$�j�npWUķ���!���� �v���w4�ۺ��/���4K?��ݴɈ0��0z����U�Ra!�8Ps��U�G��4<��T����K��D��h)���/��i/O[��)��!�]�0I��lM��n/E�*�{�)~����@�!�!_~��T�a8�QI:�t��:'z�C������`�k[m(G�i��yw��y�kt�_rh�p���Ε[8`Ifq���iܳ>�	�#�`�t
gZ�����Yq.�{�Ʋ�
���R�V�1v��ĳ>8/��<jV�K�(�~�-?��!H��g�(? ?�v ?�Ů������G&=�Q�ϒ�v��a;��]=}Bu['
����5ͩ�I��7lH���Vl�/���d4�O�Շ}}C0�b���ɭK J��hTf��)͗�' �S� �'W_�l3�N� ~�e#O�
y��Bhd��b�/�	�����ۼ�V�jlC:����To�D�\$ա�)$J�ؠ���
��09PE��K���&�*
��V5�SE5X��Z�Ȱ�*�s��=.?��c�DK~�mF:�T�{kt��ٖN�~������.i裣6%h�(Q����y�,橶��$��U	Irz���!H���i!H�,�kn�a\H�m���*��]kU��+�GK:��qq��S6	�����
�h��x����$�M;���^G�ܬuQ.ڔ@^L�x�r��׳(c��t��#uA>�B}WI��x�\'~,ģ��x�R>R;�U�X����J��0���Q[�س�Q7_I�#���і
s96�]�PR���J���\�P�w�y�Ⱉ��B�o�uD,;U�$"v���vz�[_�m�[ZG�p'a�9K���Z��h��v�v�r��՚`
X&"�Ye���.��b�Z��KZ.�����ެ�2ԪAS����T�H��w#�oٽ�s�,^M�t�X�
L�g�UJz�倞O�'z�,���ۆ��{$zf7#zN�@z�-�)��XE��/
C_���e
a���_���Y����K�z%S�oY^�n;N�k����߲p����E�}b�
����Z�#��J����J���~����`$���])��!��k<FX8Vv��fz�;�����*g˩ejgKZ�z'�.;yCk'}�{)�?υ�<��Z<^�ߛ�����Ӆ
�|gK���d�\[����#�c�ߕ�b~����d)֭��mN��t���}C(=��e-�����Z���2ѳC�Ng<#f���M�/v�wO��xm�������[������R��_��}�}+Ħ��+1"�����g
 |,���{2F�9F�J��8�c"�'�C����K���q��%|g�F��?]�/{^*��wpbܿ��/����O^�w���J,��K����e�O�����u�����>���(.���|c�l�QFLZ9�*
j�W���X��XXZ�������_��+A�ߚ��z�ÉLSi�'_��K�����/U�?�S��t�JyNS�Rr����`����B�F��%��D��.� �WX	�>���_CJjr�]����"����8|9���Hބ���%�c�}�nѝ�f'�f�7��Z?���~����/T�X���yL�e���ȫ
��] ��<S���y��Љ��\*�˹����<��T����򲊦s������F^R��y�s}&�U�K��Jy���RA��_*�e���X^f.#y�������cĿ�(
y���?��~K��P�e�CĿn����.���c�J^��#yY�������%j���4Z��8�XE���6�r~�B^�"�)(�3����w��K酒���H^��v /���#]!/ş!�w�P����l��B�ϚG*��3K)/;(����?WP'�s�����K�EJyq)����>��&QC^.z��Ԛ�����$/��4��b�����%/���)�衊�f��˚/�6WA��s�Wy9xۉ�\�/�K�����˙�e�|A^j�V��6��W�K��6�rm>�g�}��(�e�|��`�����i��B^~����K���Q��]���0
ϔ����G��\���Q��vN�׃4�!�8����*y��C�P���<�Px�%�?#�����R�?�o�O���y8J�.~�U�\K@*b٤�RQE���sP*J�!�s�XZ�(�Dy��at �sy85Ri�>n�����3l��9�����ϒi
���QЧ"��Od�<�D��[��
�ћ�v�@
�)^�1S����r6�*�V�3�NV[���(HQ&� }8�i�Y��1ГfY�{�\��y�rT'����.����џ�(�	3k��0��D9���������'���I� ��雭S��.� ?�(�M%R�k>T�O�,�)�	�����Tr�J~~0����XA�>+��ǒ��-�r0�2"S���o.����gT�I�l��ߴ�M�O����Z������f���ɪ
9A�V�w�����sΉ���(���o�7Ə�?���A
}s��hBu��T��g#�����u~�J^&U��r�e)�U7K!/ղ����5C�7;
��].� 6�v�o��v���X%H��� ��S[ߔ�D�oN���7ۧ#]�^V�e�D[90]!GH�La�e:�7�<�t$O���zƉ<}<M�����i�(OP��5��@���	����^W���K%O'&���W8�����'T�To�J� ���(�v~�B��Nq"O�\����HrE�����h}w���=���V��iYj��G����Tm1������
�B��HA���ru+_�Oo�_7>�d�.[�_o8�������l���S�/�T��Cm�L�����9��Ot��O<�R�'�b����~���~��g=�cq��5J�'g�6=4�P��Q2FLUm�&M�-ԦmZ[�e8%�F���_�d�x�S��ñ��؍w�$y��'9�_G��ڿ0L#��$Ҹ'J��\�V��� L��b���S����A�5
B}�?G2����?��f���'�_�r�����?^���,4���!��v̐��Nr!�������(�y�r�Ob�B9���Pn��x�����0���L�156�8�^(
D^(ʃHT����K��d\y�}0�O �5�"��m��s���?gC��.?�5����4��(�72]1�2v�;:A�|5�k9�/���~
�蒮}��q�Wk"ٙ���|�E�������f������J�q*Y�3�d%�g�ýH���/��Bj>e+'��#�W��m�͹���
)AJ��D�1��@"�Y��^<�,�qR>Ծ�}�H��Q��6U��F��|�ߌ��ni����\����j�C���n��C�i�T�|����PW�K�P�9.h@H��z�v�Z!}���N��^+�����1�:�8깤�z ��%P�C��w���0��' ۻ�y�8�|8�:��2V���;�H����i	�_F����
�ƾp6
ِ"M;|)/�\qXl�>
����v%��m���0M��C~���Пu�PŜ��D�,�*2�Por ����C�D���O���d��I���?��#�m��d?Q��Ч}����U�?�h�?bd�s�^�)�?���}%�G�����t����s2?">��Ǧ
���O�ݣ��c]_v/�Z���*d���n)��=)��^��	��Ƭ{)���ǐ��2��:���6y��^�UZ�As���b���9	��$l�I�̎F#��@���M��qij��}���%���r�+Z%�-���yzI�[^䜋yY�7�żN7��W�.�yJQ�Owż>�����ҟ�͗+��5�%}S���\�q�f;�E�������S���o�����h��"$>l��`?�Ȉ�cT�����s�ȈN�*}�����k�"����eVh���
��L)���3�U�?L
�4g�+��O|���k���m4�{���r[�?���UU8�>m���G)y/�����=������&D?����e��oXI��ە9�E!�������/�x�%mh1�\�Ǯa���j<<�:�]���v���)U���nRza�Z�ԧ�p�+$s���T���[�
p:_e����4�FsӃC����u��D�\�)�v����a����]�o�����TI`�ܕ�(fd����"M��GW�4��9�Dy���jphs��ZHf�KX���1� ̲��Wr���-�6<�5�:���>���.� �=W��&+~��&�5S���ѓ�0�������;�G���)F�ޙ#n)��f�q���#L�}�4�Q�0�Z�f�	�K!9�.|�ʅF@�m�5;�o������	5C��qI��cYI��*��n�ѯ�&~�Q�p����[f�,ˎ�/(��3�B��L�`���2�(�W�x͇7p-�Ԯ���|j������`�L�����?�/�[N��M����\�<l��C�%W6�VSr喪��b�SU��"�(����A��
��J�o�[���G�A~���['��7�q�1�>ȩ�w��χ�f��v�lD56o�U�:M����6b�'oV'M������W�b�+KC���Ճ ����6����Ղ�Φ��6s��p�F��������Rh�]��]h��guQ"�5_]�D�_\i#\�\�-�ª����"�{�ob���R�����p�2����)Ã5�����}8>{�a"�a�X�@j�t�h�~��6`3��.�<�1��U�_�[K��7���2$#��U�]�O���]sEޙ��o�{�doX����B��t�r���-�������So��͡��R�a�[���cZO�[���@�j=���v��4��t���L�'{?��	�։��p� :m%zO~(���W��qSxO6�ޓAj��9�}�
gI�V���`�
.�+C��n��Ay���ۤ�3n�@�Z��iw���S�eS�W���W���F2X�7�zܟ`�$C�6u��5�v�r��Ю0oӟ�����1�U�$�[�M
���`I���_q8�
���m�;!�;C["��6��=�XP��o���7-��gB+��$�ί��I�J˿˦��$�9�G.�B�H�����,Zh����&8z�Chp�5��5�u,�x�I����Q��t���2~�f���
���߽ͩR]����vӄv
Xbm��8�����m]��J�4��V���\
3�$���6��¹2�8����@״�yn��!+*G[��h�;��������I>/�m��^>�X�	�z�]3��ndR�Ϙ�ġ��F�������䓚�84���W3��.:.~x���C�|B�����Z��ѽ�KM�K�2t�`�AI)>5Su��&& )	�I�c�÷qB����g��m����MMKI�7t�.�C���~�܄�����/i������:��S=ȧc��H�V���.1)_;(%i�!9%)>!5����%
����-�K�KJҘ��O��� �_B#yx?���RR�R�em���'�L��X˴�a��L�a�:���ؤ�)�g��		S��ɉ	#F���
��~u������|�s4���?�v�����_ Ĕ���_�/5!����O�����SG�Ǉ쨿�ߡ�ȸ	����w��N�'�C��̶��{b�!	:�"�S�F��l���§��1	���o�q�C��ɠP�q#�qj�#|�?$��?(�υ���iI���i�kP�A�
e���&j`ۍY�9Z���!�x���hc���@ϛ,�
����{���2�$r����+�Runӭzsȥ�˷�k�K诛z#xթ9�z�v�������u��:R��"Mw@ü���^[��V��
K#���޼u�] ��I��qVϬ�|+MY��7#&�u�,J=자�C�H�}R6�`�:��29�fnNg/]=�*�>��P�צ>��G��0R�E\ɱު� Z'L�:�����CnʯC�KrU۷�vu ���5��G�9��a��?[T��i���g���*5��u�h:���W�r�3ݰ7F��)Z1N�7�qq1V��l���:�)���'n�L1�>�����l�x������P�P�Dw̟$���k�ű���O�p��Y���<2�"���"m͠0	���*��&�N5P^EJ�N������%񛜲�y��.��]��"�R�'�4���4��Qz���Cl��r6J�@.�Z�((	����,��3��u�­�qR�oq�,A��P�ą�?���H�J��L\W�4�O�md�>a����H)yHG��bu�J��<	�a��b�:*�b�w��'�"���h`��,���t��K�	3����Ťأhf����,iɟ�;v�A��?Q�$��cR��)��EcF9"��J�^j]����zؙ~b���l���ڮ^��1�x�̽|SY�7~�2Zi7�.jW���-t�:�ѦMچ�M&I��ڴ	4�6�$�2VQ;����UQqD��**�u�*�.��n_W�e���+?E7��}�s��o��߯.���y�s���?���؞����D�y�hG�����Q�Ҳ�u�=�)�E7���\vSzO�X2��5�Ǔ�x�����a,5���&S9׮�d̕�����=�K�|� �m�J$cZ_*��<ގ�@װ�c8��
�<����t�
b� �q<i<�xd~zϰTb�w�s�cѱ��0B ���2|r��%�z�
�#�~��{bqa�T6�i41���X� r�Phn��7���qA�;:%���ʋPF�_G҆]��O*,Rx>g͂k}��7r��C۝A* �ݗ����)D��4>����56�Ƥd,�e*1��ʑ`z*;N�ں�Ҙ�J�hr�&��]���x@��V?��^f�	�E���+��y�e������x�Ao��T�\�`�T\�W��p!�& �JPD�F���]�%if	[��J��w��̞��_,��������/�
���^�ݸa������m��L�Q�!��U!�[Տ#�{<��I'c� ~kY��
�^���d���D2;�x|�H�ׁ�ޯ�y�^w�{?N|4��ϰ�]z�z�M��f�Ͳ�B�b��M�2�,�sh s��w�<}=�>�-1�{ˤ�F5S�Q^P�2	6-�ФY!��ҋ2�qxV�HLěs�� M�s�R�=�h�rH�=��Α�ɍcB'̒\\3"��v�~�<Q4Y�L%rBw�����p<̤��]��O-7��o819wK�:��n>+7Θ�� J�ci"��$Q^(E:��S���Mzp��Ї�DX�C,a�x����	�R�Hq�2苑1(��0��%v���^n���!��0av��H�dQy�ԇ5�q�Ԫ�yK�Ȅ��4Rw�W�3{ �.&6����1bsV�r#Vd(��y"Eg��)�ٽI3�I�c
k���0�-��LI��
�mJp��R�l�	f�9X�{c�)�J��k�nŽ�|��fhi�E��!��YI	)_�+voբ�
���Pٵ���*�_��&�]�~�+Ky|���?�^�29Ws�~_�/���F3���Q�i�I�<V@6�F
���%+������5�('�$Y�Tz�A+�|��q���0�wjQ�6]��x��s	�ӏ��<����9�ǃG�4c��K��§�2I�_;���z	���X|2������a�4B�&WXZI�V>ݲ�a^�iXv��/j�n^f�!<:��,̞.�����f���4RI�MD�B?�sI�7A+�Q��p��Dn��1��`�%x'�i��%���44�I�]��ދ�`�v�h��&3��ntYqib���eЈH#������{яN�'�E}!0J�hN�'TaY�2j�I��9�(�3�t`r�$�+��E�^���kiZ*>9F��L�F`.y�F�տ+SbzwY�#�4et��JGd\��#��=���}PH�Jd��l6QNW�2��ɶKP��M����4{�yVu?
0����⻢S�:ȉ4a?M������#�bLH�څ�1
��7�R)T�d|wtl�����E��D&7���S����$��e�>15��1�����(d�MR8Rcl-H�SZ�b���Ek{���b��p`�TB8@38�	$"r� /3$E�kRL��!����@���,͂�N'����
�DX��T&���I�f&kst7���PU`�`�����R���jl9�cJ��#r���Ơ�1��JsռC�P���`i��
��@nf�Gb�zD
�hf�P��	d�UՍ*���a絼��b�a�Y�ɋI]\�\��h��GE��&wdɣAqd֐��؂�Ƨ#�5F��g�V�Z"JKe2�fm܂�6�Z�yl,8R���|l*ΈS�dl7��j>@U�N��c�D,
�������
�K�P���glE;-�7+�����"��LMc6�k*�K� �<�5I{<�}�DN��Dxx*���m¸ڒ�%{7JK-$�p�dؐC�!�J`5���]j"W-�"��dj�J��Ly��F�,��Bͭ\�gY�f�YC�2�hRZ*8qrE�<k��jX$Mr�#5� ʹ|�Y�\Idɪ�\K��sVv�ٶ�~������:4j��$S���T��]vO"��3<�g����LQ<��$��x���O=xgrVw�*�i<G��s�5<k��O�[��x���s�%<74O=��������P#�5xnL��x��9����x����q��smt�9��$�#x�����ӂ�����~inI[�-����NTU0/�F��~ʛ4�-��b�wrj?imx*�_�Ӊ�ɗ������_�-�C@�d
7���
�G��h&�vJ�i1�T��B��:4sdf��v$q?�73�娇}ݖ魣w�M4Y�~�1Bߨ�qe������_������ѓ�[�>��^%�}���=�\��I�3�!^{TZ�@w�o��_0������΁�/�ݠ���5Ճ8�n����ߠ�1Qy�M���9g�v����������5��B��1�/��BN9fbCޠ;d��R�B��9����@8b�ے�6�H�+�Z4�F�Zܬ��F�a9��L94ݡ�@�
  typedef internal::Types39<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None> {
  typedef internal::Types40<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39,
      T40> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None, internal::None> {
  typedef internal::Types41<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, internal::None,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None> {
  typedef internal::Types42<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None, internal::None> {
  typedef internal::Types43<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44,
    internal::None, internal::None, internal::None, internal::None,
    internal::None, internal::None> {
  typedef internal::Types44<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    internal::None, internal::None, internal::None, internal::None,
    internal::None> {
  typedef internal::Types45<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, internal::None, internal::None, internal::None, internal::None> {
  typedef internal::Types46<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, internal::None, internal::None, internal::None> {
  typedef internal::Types47<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47, typename T48>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, T48, internal::None, internal::None> {
  typedef internal::Types48<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47, T48> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42, typename T43, typename T44, typename T45,
    typename T46, typename T47, typename T48, typename T49>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
    T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, T30,
    T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, T45,
    T46, T47, T48, T49, internal::None> {
  typedef internal::Types49<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
      T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
      T41, T42, T43, T44, T45, T46, T47, T48, T49> type;
};

namespace internal {

#define GTEST_TEMPLATE_ template <typename T> class

// The template "selector" struct TemplateSel<Tmpl> is used to
// represent Tmpl, which must be a class template with one type
// parameter, as a type.  TemplateSel<Tmpl>::Bind<T>::type is defined
// as the type Tmpl<T>.  This allows us to actually instantiate the
// template "selected" by TemplateSel<Tmpl>.
//
// This trick is necessary for simulating typedef for class templates,
// which C++ doesn't support directly.
template <GTEST_TEMPLATE_ Tmpl>
struct TemplateSel {
  template <typename T>
  struct Bind {
    typedef Tmpl<T> type;
  };
};

#define GTEST_BIND_(TmplSel, T) \
  TmplSel::template Bind<T>::type

// A unique struct template used as the default value for the
// arguments of class template Templates.  This allows us to simulate
// variadic templates (e.g. Templates<int>, Templates<int, double>,
// and etc), which C++ doesn't support directly.
template <typename T>
struct NoneT {};

// The following family of struct and struct templates are used to
// represent template lists.  In particular, TemplatesN<T1, T2, ...,
// TN> represents a list of N templates (T1, T2, ..., and TN).  Except
// for Templates0, every struct in the family has two member types:
// Head for the selector of the first template in the list, and Tail
// for the rest of the list.

// The empty template list.
struct Templates0 {};

// Template lists of length 1, 2, 3, and so on.

template <GTEST_TEMPLATE_ T1>
struct Templates1 {
  typedef TemplateSel<T1> Head;
  typedef Templates0 Tail;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2>
struct Templates2 {
  typedef TemplateSel<T1> Head;
  typedef Templates1<T2> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3>
struct Templates3 {
  typedef TemplateSel<T1> Head;
  typedef Templates2<T2, T3> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4>
struct Templates4 {
  typedef TemplateSel<T1> Head;
  typedef Templates3<T2, T3, T4> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5>
struct Templates5 {
  typedef TemplateSel<T1> Head;
  typedef Templates4<T2, T3, T4, T5> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6>
struct Templates6 {
  typedef TemplateSel<T1> Head;
  typedef Templates5<T2, T3, T4, T5, T6> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7>
struct Templates7 {
  typedef TemplateSel<T1> Head;
  typedef Templates6<T2, T3, T4, T5, T6, T7> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8>
struct Templates8 {
  typedef TemplateSel<T1> Head;
  typedef Templates7<T2, T3, T4, T5, T6, T7, T8> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9>
struct Templates9 {
  typedef TemplateSel<T1> Head;
  typedef Templates8<T2, T3, T4, T5, T6, T7, T8, T9> Tail;
};

template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
   ��F8K���j����3djt�J��������t^{Q��M�3W�dɦ��b6SJ�E��������|�:��C��E�|;'�Z�S;�y'�=������}�P��P���.U���+����ϔ������W
�m��C�U�������o��,�߸
��p�����F����m�_��Ɔۈ�Qʻ�){v��׼�(�e9�B3V5,�R8�B���Z8��?�_�{��˯���gE��gk�?�j������G���պss� ��¢�<�?3�O��ρ��v翃_��/��S���p	~ã�߆O��~͋���r>���,�p�E��ρ�����?��%�y��� ��}�����{���_R���1���-��Y��?�>�e��u����}Sv����#�x��3��������|��0X��b������{v�JTU��"����~����E���M�Rn���-�VM����{Wc��z�C�>���R�.���o��r7s�9�h���
�ﱟ[�8���_3��%9#��_�
v�Vt����������k�\�Q{;�~�Ѣ��"I��?f�7$���_���px4�I�wl��Z�g�+�K�W}�Q	�:��>^����<��cয়�w���h�5�g��hޮ��^�q���<�=ס����霩�h�AW�wJ��1M����Ge>��G��� �k�L�����2�ޥ�{8�����Z���>
i������`��x��C�ì��o�����b�C.���x�\Ξ��;���/B���������R���qqWwǌ"�Տ;x�Ơ��������
������ׯ�t������n���sj������A�#�u���?����O�������/���y���|����7m��G�K�u|�����u|'���^�㻬X���b��u|�W���zqn�؜?d���9^��O�'�q�X������~=���u{��u���������z������������a�_��^������2���:���u|��������t�������oz@���z����[��ﾀ^����L@�>����[�����7Z���G��;2Z��s����E��p��'��
��b_P�go�~����_���~P�/��rEH�/�Bz)���s���R��ˌ��_������_��������|;��l�y���:��?�D�{����:�����/���_ީ��<>������qH��g!�_�t����|���}�UH�?c�E�����p������%:�KJt�W������?X�_�%���K��˾��r�D����䶿��Dϯ�=�������� ���^�������K�O�_ea=�������fg�0^�g;��T��6�R}�=�7���?�.5�p�#���_����8���_����K��(�8_�#�����Iy��^����U���ۥ:���//��]G�ae:�>��2�m��-�q_�����Ҏ>�<g��:�(���a�#��վ��7�_�
�~o��+�>Ǭ�yst<%>���Z��}wمͣ�g���p]�>�0�}�_0׭��Ko~Q�[��@=��E����n}�:�o����s�߆r��=�n�����Wx
�ݎ�N��w�ѭϳ��={ѭ�ӏn���w�ީ}�up�mG��P�����[��p���/�C��Qq�h��˦�v>���οO�V���|�v�g������t�����6���%�:6?�`!���)T��|���6oa�B�{&�O{�m�At��P��,�y
փ10&�.0	v��`
L��3"�ׂ>0F�z0���&�n�L�i0z��}�F�(X��8� ��$�
փ10&�.0	v��`
L��3��A�`=�`��`7���4�=7�>�#`�c`L�]`�{��3����A�`=�`��`7���4�=7�>�#`�c`L�]`�{��3��f�}`���`��	�L��`/��`��B����Q���q0v�I��S`̀�"�}`���`��	�L��`/��`�xi�0
փ10&�.0	v��`
L���}�F�(X��8� ��$�
ښ\'��6��r���';���/o[����s�����w��"S�gO<�fκ��Ki\p�>�6���!Ϝ�7M�s�y��?���v�y����%�J��R_��ݗ����γ�py>\zڸ
����æ=;~_5��QO��'y����.S_�w/�����K+=�|r�._h��k�7��Vx��go�aS��«�>��=���|�|��cy˟�`�y��c�W�ԯ�~�9��1���_E��	g���|�\ޜ�_���}��G���i��l�=g�`�ԗ��-�?�����ԗ�тm�6~�A����N��������v�SO�_�:�������l��)��[E1x��|�E�?��
OPЪ��Z�Ŗ������H��"�m�����6���նʳ1nu�]��]}]������ri���J� O(JE�ʥ��sf�d2m������}~h��wf��9s�̙�3ϝiΉf���i�ք���,�����4ɦ$SO��� Jm
����!�&S��|=�:���/����4�����od��o�8��ʋ1�-<w�4sV�o�)�;�g�s/�߫������>��o#�4���t����{�Q^��e
�6�@�g2M�:�����^9��k��X;��w&fa�����G�����T�UqQɽk4K�ɓ\���5����%�Y
�2�5|V��6���;�S��x]�O%|��S
#�g#��������0����0��]D���u��c�?`�ηa�����ׅ�Ä0��4��ņѷ�a�Fn_��/a���{G=/�~��{yn
C�0�\F;���z���3�x�F���
S�%�KM�%���f�K���[r
�-沜�[�3?�=��#%���|x,�w��߼�9y��GƳn ��y�-K�T�9r�+\����i]S
�Z�?��gB@R�8� #��/G#%��h�IFI1X�
'���j�p9�
��jN��BF�됖ѽqM�I�b�U%�5��b4QLp�ii�3��rN�$F�⃔ N>��J+YT�����Id~���LɄ΋�.�I�s�/Z��$m�e�(�0�i�9K���
�T��__|f
�����u q��Ja��	
Qó2�ygg9��3�t�R8���3��3�;ˋ	�99ˊ�]M ��|0w����,[T�.��=���g��,���|7ĥe��E��,]�d��5�Y{ia��%+~a���������*+X��/-�U�EMae%�u�-�/ʻ%�$1!#=�x~����E��e.Wq	8�i��=
�۱HeRqi�y�wZWS����\y%��g�1��p�C���-��j	XO��i�`��&KVZ<,�R���W\���,
����p>4�M9�� @�=��bM��g+$?i���t���3|���������F���ِx��	!��Đ���R�;r����.p ��4E��:�#��0Eç���Q�2�����g��y�<^��r�O!��h��>�+
���SH	1�k�φE�J������6��T>����O�e+�`�/4�i"MKx<�]�hQ_�c=�(�F.;Q/����f��>���{�f�/�:���1}Ʊ<
�6�a��!�i:��;���R�u/��Q�<��%v�9��s_�9�ڛ����Ⱦ�Hx.O_/�I|��Y�[n��N����n	�r�U��8]�[9�.��7M���zZ$�e����}�X	��x���p<^��9� �O����d	7%1\��V�>C��9�-�VN'W��8^(���p���.bx�L�����&2|��'�rk$�5�����q�\�d��N���A9^/���f�9�"ˇ��v�x�܎v�벾���r�r�CnGN�t�$�[$����U�ko�z.�-��$<��c�L�o0'�t8�,᭼U	����,��|eKx�s%<��^�q�\.��e�8^!��_%˙�5�8�Z�M�p=�p+�������O�z.�_�K���i����\����Y�;x;���s}��������I�8n��Z�[%���^��8	o�x���q<A��9�$��O�p�n��z���!�U��\N��z.Ṽ%���u��]����b�U�|x����鯖�8������52�������9^/ד��r{q�E�[8�[nG����8��m���]���\�%<a)��i�x���"�V^�U�3x;�Ix<o�x	w���,�-�~���q<Y.�㪄�r<C�+8�-�5ϕ�V�Jx�]^��r	o�x����q�-���c���v\-�ke��v\#�9��\O�����۱Y�c�g�>�-��W��lN�]��O�L������U�]�~���r:qrz��Kx��$�8�d9=��Jx2�3d��ϕ�ZN�P�+x�sIx�aWeܰ�r��/�����Z	o�t��8/�N­�N��wz%�-\�$�f:׫0�����.��4�W���2%;f�%|5�Ix��C����힄�\��*�{��%�f&�+	����[���Jx.�O��'s�ׄ��Z�O6��΍��H���['���z	/��6��y;��r3�$�������.ᵆ�Hx��'Y��a	_��q^k艄Wz"�Ɇ�du�W�L���*�/�z�>��j艄���Ԅ��Z�gq=�p��뉄�z"����z	�m艄�\��D��W�e9O�~WV��	����]2�7͐����Hx=��U��x=c%��σ�ft_�x	w��$�t8�,�9|^,���̐p+�g����<s�ԳP�3x}\���
Y>���$��׳F���jY���a�F�x}�$<�������,�5�~�z���S��׵���.��������A�?��E�+���V^�X��!�~Jx;�� �&C?%���O	���H�\.���7t�w����zN�\­|\���5<�J�cg�p����r��r���&�5��O��U/��v�Y��aw�����y}t	����:�{:�^7�뉄����K���� �	��(���d	����U	O�x�����B	�m艄g��z"���5a謖pޢV9�:�/���Y���t�=l�۫���3�￻��|^�*�#/�]�U.�Yn��L�R�9n��\N'V����J���	o���%<n/��$<�����_q{"�&���j	O��٬����
	���]a���Hr���%�x.�|^(n�W�랾��{�)x>$#�w��+��5a��p����$!�x��7��[��ap����0xr<;�
��
�ׅ����apc}E��������ǅ����ap�ϕqï���0x�Ў.S��*��A>7	�n�#��%��0�{�0^.��0�����q�;��ׄ��t�'����,��p������&�`ˍ��	a�$�N��'�����a��#�~��o�I^/��D�	�oE��~��hQ��8�'+��v��"_~�����N�G��
�5"�^,�+���E�gx���r�<o�|�_�B��������&��(�w)��.�G� ��}|I�S�[��*���%����l�#김��BW�%�V/p�
�SY%�g��)�D��s�~'��z+���{u~���~���~���>H�[����"Q�<N�go(i�KD}p�hW����]���*����Q�|���~���~���>L�O�_�E�����Q�|���~����$꿀�E��1���XQ�|���~���~����,꿀���/�D��TQ�<M��(꿀����C��,꿀O�_���������TQ�<C��&꿀O�_�o�_��+��<[��%꿀��_���/�7��/��E����x�X��C����&�����E!�ղ���?�bH�������i����.=�8��Z(|�q���S�7�q���Q8����j)|�'�q���P��q��UP� ���>���0��\
�aR}ށaJ}�~�8��(���
��(��8������e�(��qH��wb�/��~���
?�᳈
��g����
ߊ��?�K0|�O�1|.�O�y�%�)<�������
O���?��cx�O�k0����1|!�O����?��1G�S�|&�)|�/&�)�×��������������_F�S� �/'�)�%��
��!�?�w`x(�O�1|�O�������F�����?0<����s���?I���`8�����N�S�wA�S�n�$�)|+�G�.��h��7c�j���0�D�Sx6���?��c��1<����x�%�)|
��u��	j'�>�)�?����x�½1<���p�S�
��p�O�#�H�S� �'���*�O�O0� �)�Ó�
���)�?Kq�������L��S�N�3����v�aB������T��sTOr��uΖ3L�z'Y�ʷ�j�Q�֡j=��U�U;v�EUkV���ެ~����0��7ь�B�To��6�ށ'*��5�BZ��Y�����O����Q��.��Ô��

�k�;�`��d�u쟪g\
 roD�;�]��j��. ƽJ��5C|�S+;�-���f6\����Z�\�x�,%X&�_��������$ծ6�ש�F��Nw,{��a�X~�^Ÿ!@�Tv�Z9�"� $�}�`�8���[`XW�Yol�6AB��]���0ȧ�:SY�M���������!Iˍ4^��L�!eFJ�C;5#Sվwh�w��?����'�R4=�Ve�t�y==�I�g��h��T�a$�@��A ��1�Rm����R ��9��O�Y(˂Q6
e@(�g�ٌ>�֨7���uN[��.�x7�A���Y��+~Eٜ^��qjS2�C�� &ǯ���0B3-U�?x�$��̿��K��3�t.�i�oLvA\E��L4U�
��	�\�Y������
�T�!U]�������	t1��c�Ԩ��o�,�XZ�N2�kR:�T��Z�ޡj�A"�^�:K��8��"ͲY�(7}i�`3d��z��+P����
��GR��� �QN[f��nj�x�����o*��OԳ?��v�H���d@Z��$����F�5+U?���a*26B��C�H�j#T�&[;����o5tգ*J�*oi�hb������Pdb?T�m���z��( ??�������&�(�B��(;H�Ơ����fa��n������ �b!�7ʰ�G땴�U�Jո�X�aۂ��Q'�l��W!e�;JV|����>���I���� �i��7�wY,d��-e�"U{;$x�V�T�yv��K(���N�}��<DQN
��-�R=+Ѳ׋���yi�${�Ll��(ZXK��F� Q�g���]Q����cC�g��XjY�iK�H�(�'o!��'�E&YO��mK]���#�=�N�˶X"v�Mi����rZ,��J3��]L
�)��);3�oQ<���9��scZ|�AuӦ��L���]cZ��@�qCcZ6@��3�D�� �]����Zn6��|��E&Ge���^����{T0J�`&�^}T�nE����:����Q	&u��w�?l��ԧ��ܚ��#Cupd�6F�֙>�ѩ��*k7c��B���Ũ��އ�FA�?����F�<*�VQ�����@Nm�ѯ���=�U-Q��@]j�X���m�V6P���>qT�p٬6�P��5�rr#ʋP7�/ڳ�f�c[upl�^Ӆ��:���g�O�gva�%�N;�tT|�2�����05�?`�S֗�hKc��~�_?վ���nT�U?�w�sH���a��qu���w&�`�Yj×QꐷU3x�������~�N�|0��u�^����`a�vG뇿cHi���|Fz?�H�ɚڛ fŌ	�l��ýU�/}wY����M8ۤ��]6���87�r8�oe.��"C��!��ш�:�����c��X﷉�<Xc-
%b)
�4�
&�J�W4�J�d7�7x³>��v��[��n�E���lP�v.�>� �S�4���T��L%�rf����)�=������Z<jƨ

� ��,k$H}'KM�[�-V'ل&���Ʌ?��O�O׶������{?�������i�'������o�m���^��!>G߫g��F�A6�4"�ܓ��8V��.�68�ı�	
Fj�����-�DÀ*zS#sO�B[�zoF	����տ�&.�T[2S��Z(2h�~���&�9��[Ps�{'�e��#�+5�'�HI��|�z��k�^SI�Y�_(A��{$�{G�A6�=���M����)4zV}�d󎒀҂��Qbl
R�����!fQs;�x���lجVZ9LU�����c ��O���]�Բ���m�I���଺�l��	����bz�����i[E`zE�U�G/0�|]pU�u�vH,�1�W�KDJ5���n)�q7H��Z��"E*�rum���Q<Λ��}a��vZ���e4��FTOEh��'Z��fч!���S�E�nD=+�_������+x/;)��C��es���Y��r���+��dxM\��n����G��~��7X*��8���1}*�!ߏ'��ԧ�2�b�Fr�������bv��l�d�*�� �"`f�p{�j_������M$�[��@�w=�m�w�L�Au8d��@6�ա�sO�Z����-��l����<n�s�����U���VVy��Bϳ��Op����Y�;�0}:ξW��r?a��,��H& ��}���ĺ�F,�یʹ�s
��N��/�b�]��G���b����9������W������k�	b������?1IŶ��'V�9���K�u���A9}pȵ������R9�Xt	���+n����d'kr�j�w��}����ϐ��V���������	.6�}�.�-��j��}�|��`*;�3��-��'���L���������";5��z�:�z��W�����L�pj���4��RР���x��$ V�'�;�ǐvGCG�S۬�Wӫ�︨��uO���H8��N-�ܡV�`�7��?ֿ|&Z��6,8�l'�܉=�j1�^���@Md��V����{%M�!~G��(Ԃ�I�S,�&ms�Uo�5�|YH�<Ò�)��L��~R�zO�i���j��9=�����G˽�� ���X֊{�Nm�:�7�+[����qN��k��Ծ��Χ���?(ku��aU�|�V~Ѯz�����OQ��P�[���ZY��Üޑ&��}����GSc;�3�̺��ͷ�7�]�ao\�D)h�K�
p=+-�ߑN�?L��7���0��O$M����J�OeU��Ӡ*�cu���)�W����HD��#ݱG�ϭ{�~>�Y�~�d� &NA���=�A���~�
uʀ&u_�պ��[��a���ީ��6�¶�����P�����Xp��z'�	�-���;��s3M�9[j�\4��3�v0�\�z��zc�ǩMQ6�r������}�*Uxy��ԃEOd�<ca:7f�M���O��ZG⎶��ztR�6p�[�� ��Tm2I;���`<U���]ЩT� r;�8N��p�!I�C���T��Sh���wb��YA�+�X����3U�-P�7�oSiM4
l���̽J�F�l �@�P7�4�C�����>Z�N�fk�qƂ�zE
�u�
p��qX�j8w��q77����`�5!ܕD��L�j���T���y�{���^CHU�t��/ށ�^k�����HC)�7R�=E��{�[�~6�̷�S�|�6��������%��"�k:��Q��L�7�+�C�
Ε����{��H�2�N�$z�'
�\��~]���+U��Y�h�����JuM$�^�1d�Ӳ1B{�յ��k����:��_�ɐ��Uv�wk��%z/qz٘��}�v������e۩��5�~`�N�ד��k4-�a{��o�*
������\�@�c"4E?7�S�#��zt;	B�V����P�i	!C���҅��獺GY���/쑪�ϵ`�4�^���;��A�W�`e�ve��4e�V�
�%�)���]�� �_Ǧ���;�(*	�؈��x��oRQ?ѧ506�!��>R�u�T�g�K_��I?q��o
�*����EW]�FUGUR�m1�h�����[Ǟ��~ls��m��r�B�&��/{㌲Fӹ 'x������\�[`d���Ry$m��h����A6�QvVi�EFJH���-��^�`��u�w���&Ks�q.e-_��;��g�lL4)�`uW#��X_����קQ�a���2~�5Rf�v����Ğ�z*�K�k��,C��1�J�Ct��_�=�e<���M��-�N:|�a��lb��ys�脼��CR���
C�`�}!k�)Bɳ&���1�d=7��
LUK3��4���:=f��3ՓbI�&Y�4����zꮲ�N.>��������@���cx����ެz�$�5
SE���Ae`k��hJsIw���2�AS�Բ��t4B˲݄��ja{�$�<���e-���vp`L-�#�R�#�Mꐝj$�(��,��|?+u3��5y�4�"�����P�{��/>�~G)կ����w`E25��d3���_#-����p��5��b
��O/$�~Bo
|p.zP�a��@X ��bY���'����_�
��j�)�#���~e�OY�W��Mt�I����������K�*mܫ����
)M;�=��k�[E�k�
iA�D�+JI1�b����z2��H�՗���̦��y��]�i�7�"-��W7�o�D���V�|���u�p��i[+�|���f�@��� ��f��]��
<���,��ʭV�� t��2=��b�>5Qxlu+=a�[^���r�Ԙщ�٠���u�>��6�(�Y͙*���OEt��VE�B�&�=O�@��`���zV�J0T���4$IP�d�*�Έ
ՊlA{�]O���ZQà��Z��	�V�~�U�tj�BD��<*ЖQ�^ 	��V�A�H��`Z�D�$zo�
3�QP)j����ԘY�+��dDq
��ACf}�j�B�8���F�c�]m4Sk��z��I=�{0�8k]�z�=�����z���qG1ِ��y��mIϠz`%P=�^���J@=�C�c��t���f�wK�d4�$v=ѹ�F�[�ǽ"
Kk�?��㗾
#�
��H��_�-�W���E�>#ۏ��_d�Ϗd�[K��h,��(�*g��x|��W%��a�{y���������/�����ͱ��$������6���a�ʓ�Y�7a��|קFv�]�f'�[?�<�� 5r�P?`B� �G������v/8��D�X�0�F�z�iou*[�4�K�H�!�R�/�c���_ŉ8��I�����e��;y'<9���}*V¬@��ԃM�V��9��ofcd�1Q6�����и�e�(�����U�XVe#���Tp������6C�0;쇖���d��W��Tϥ'�;��a�ٖ���搬˷�T�-��UD�C!N�u��]��z�ֆ<�z���@=T7�]��M^�̭��b�^�5sl7����sL�`B}Eznw$�X��X���8h�d[����X/�um�,X?��� ���6�>G��el���l���k��ֆ�잀 �F$]�6�
#�o�z��A3}�c�1Ϭ�(?�X�^�
U?y%���߇f�
�G��yD�����I��8-Sp�T��h��U2k
g��(��pQ�SA?���>�,���mڷ�ƨ�n��Փ���O�Ҏcy���8�w/�6|��Sϧ�H��K�_jœ���U�l��>�+�%�oS�M�����Y��/e���'��Sֹ2���
�x�F�	_zQ-;5b5���6�td�MԺO�玌X���i=�1��`�zj��M���l҂Zf�6=�;�lY�Њ+m]��D!���I&ާ~/S�bVΏ�xB���2|[>3*�m�G��?=�T-�I�!��t�%$��K��H߃t>$�=��5�Q�1���8c�]KN��4F�=ۣ��H`?��b����G�b|�bvf�7O�����O��ꋩ�n��U�`�x�D0�h}��[~N����"H��Ip7
Y^X�H���}$�v|e��=�&V�^ϙ��b���k�b
�ǀo�ph���3Um�Zy(�.~�/?ů��	f5�����侄��[/4a�ǙF[����e=�q�e�I��"0kM�ĳ��|�h�|{��� i�oށ�ay�xm��˾�����It�c54/x��h�rk�q�oK
�C��y����sq�ݿ�w��"��FN�/�uƯ@��T����������h �/�}��`f�H�O�7D3]~��y|B�m�~��P��y��a�t9=A)��X�V��4�U�/��������ï�!6J3{������Md-�o�x���$([ߎ�}L�<����%!7B�tg���Hz�A&����h���&�剆����NU�N�f����z���R�%�4�s|�?�G�:]�+Y~oh~}��s|1J�5���'v�g����^���u�?�&��?`~�?e����c�~~ӎ���r�-x��s����9�����г\���qz���:���iv���ҋ&�c�Ն���5X0W��}8�:�0F�j����;{����D�b`��&��*�u?��=�n.���{��vX���A��苷XC����p�o�#,��Ū�[�`�S�'��g�IP��\o����T�@}�߰�M�U���s����
�g��X>��ў�ew�m�@�� ��#e�B;����¸y��1�N¡�*��
L�8��Zӵ}�+�J4��J��?O	�إmg��vT~cV��!����Qy�p� ��e`�+C�i3�
�Wl�֢�!�Q?�3�}d��AJI��	�pAOpӣ�t���#C`>�T=�J�6<T��s�pXB�Vvm�vڑ�Ұ�[,� &{����U�4j�O��"{����<;Z�ɡ� ��'��8�NT�'�|�ON��_4_ɲY�>"&�iV\������t���8ƼvX����i�:���S��j�U�RF�$@���S��l{�=L�H�0->���R�`��~�>W��v��N�"K:���Kl�x+EY���F_J�5O�9H�=�-X�L�1���h��5z-�a�gZ,^�zg���:@��ER6��S�;����-�LΔUܠ;�1N�M���I�1�#�%��g�/9,̿�J��{B6@�t����X���e�[�{�Ќ�d�v�3��I�`/���OgZ�؍FO�[;�h�2�w��A-�>O�^^G�L�Vˏ��U=��f�'5���9?UY?=
�L��[�B�Hr�E���<PkQ�C��pW�ߡ��؋�ߺ3�m0�+ƨ�z>��o,뭬W-�dKپT�T�(�3���h��K���s��6;��C\��>:��t_�C�nc��ʯ�uzG:
�v5�ZX��uˬl��Sf۸	�$�	�/_H\��g�� �&\|�z/�6�%������S�G���$�G
7��]�nin1���C�~�Uؠ�K����w�Ü閔
�]
�5+�"����U��2���G{X*�À�B;z�X�=������GǪf<=ؾ������<� ���6���o���V&5�8��yz[����Q5�6��/D���(h��x�@�Ao�(�!e��~�0��`�c>}l9s�&��4��+;%�ob��.�-�,V��c�	������(���#�u��rK��i�b�{lt72~��d�E��d-���M�NN�)S0k�4���m��aߚ���?�����;�#K��F�q0\�'=^*��k������%���#z�]��5*U
|�Q
��/,�-��q���̟]m2��zѾ�}*8��kX�|�6�BA��E�tc�oa2�M��{:��Mp3�Of1-v|W�w*�H�j�ڕ6��|vM�cf��»D���tinӥߗu	�!b���5����{��K����m���݊{��� 컢������F0f6����ouzKa��FJ�`	�ҵ���ѝ�/���_�0f�����z���ro$gs�R��C{,��Xݓ�&�O�/�a��(�Ws�U�V�בּ�Y7�i�<��b��/��=)�{�����d�W�C���τ��Fi��*Ks��{Ώ�=�G`����n��Z�.���t,��@���d�Y�g<��8q��pF��p۴:�ؙ��(;U��r�u�·9j���6��uƞ�����c��N����{�tD��-a�N-麳�������2���/A�h�{�S�'#(�X|��a�#�_��MEF-aǲ�J�5�{S��[�a�~�%�c��{�lS�[�����%���18T�J�#6�aE;쟗n{
*���U�"���i�ͧ��w0���8݂�#�.���d�T�!oT��w�(�'^��<��x7.�~i	��Ü��h���B���O�>�z��}~������٠�����2���7?��k~��n���x�����#��'�g����+�����n��0���|~�&g����:	��ω[�+y3�Ex�^�ro.��B�
IЂ���ɯ���N���x~�~���ШW���ڦxS�L�ޱM���c��x�6`�QȂ�_u~��G�/���C�*ԗx>�gϯ%�����'��"M$V�#����&��n���6~^�_^�^af��ǐ���	�����������-<������0�39	�1S�f����u�s{Yh4�E��be�?���*i<� ��@�E
�;��w�x'ŎW�:��1H�H�J�h��Xp���V�<vuO���ˡ���ytծ.O��B^��R&���Y�q�����l%Z��N˙��]�+º�%ʋ�!�}s�J�����i=�ζ�9O@���S��{�>m�=�h����?O���!%�Q�n�r!��=���*Z͢�
��POm�ݢ�>����\�b���+Z�M$
k���[Į
1Ȩg�Y��ԁ?#�:L�J�>�a�=<�H�~�QP"��
4a\s+ǟ�FǑ��0�5Y��TW���h���p�8�N-�:�\��ʍ �Z�A�l頙���Y�<�#2��I�:ob-d��a;%&���4)k��mE�pa�OVfN&}~��bl�4���N���8�T�>7�X��$�?_7�	a�w�H�tR�?��v����C-��l��A{�8��DV� %.b�=V���U4��I�k'Q<P�����T˪��a,?@(�Gx� �d {O)����m�N��(���^ة���ɀ��G��z�� ���]U��>���g�����#�a�q좿Ǳ���bK��
ս�c�՝ٕL�~x ��Ј&Wj���ށV��.��/|�S�Ł��˕��I�K[D��HZ2Uvf;�CZ�t��z���i��󜸽p�[Ь��9��	<��?��P��f��%��X՞�;n^
���5�(��Z�k�R��P����6��z�%Ak�#�tR:�A^���� �f�DTv=��P�5G���L�����W��)�BzL�9��86Qwf���b�|�?��(T�g��Ĉ'��O��רY�N�.�vX	F�I��>U�
��Jj(�2EL5���G���
��琑�(�J�7�: yX��{F��P	
EDcyEZ���ZVϸ�ܣlv
��L�/~#On�b���*L��x:p	Z��DF�,I.��;��t�E8u����6<����lHFv���}�ni��0�p����8�Y��U�Z�܅D���>a�dc�Jĝ���7��h�a�|�~H_� n
�n��琹}N�
��m,1���R��.ُ�{�AK�6�(Jx�9����g9Q^�>��$���������4a�'�%�<U�*� ����Sr*i|{�'�g͍��V%���c�b�<��s�4�"?�V��Ǔ\a�r��
S��W̒,�d�GN�W����V�4��jS��i��<{�tDz.�҆o�Y1f���ҕk7F�T�ʆnVw�_m��3�V4g���Ufl�>��z�mStQ�7���:e����
�w�^
f	�.,�[�'̏L��{O��:z�K��D�}LC�b�?�Q%��z��V���.�C����C���c��#�qk�k���LĄĸ��>N����*1����4�HS�r��>��fN[#���:��I�>��u��3�����y��D
���,�y�J�<py!�M�G�a�8Ȉ����Uu!�P��،���t�y#���rdǶ���vR🡠�D��'��{�Q�3&y�YzF���ʻ�1A��}Ap�4
&�v�@�Mjpa��������n�Wb�(��ӌa�$g:Ɠ���c�����i���%g������c��̂���s|L����9��\&�8���X��/s� ���6������b�V��rϵqDє��Ϥ�r0G�T�7C4V�N���Y�a�q}2�t>��&y�Yz�L$�Jsێxw��c���
��转N֐=֯�W��s;St��ӂH�X��վ=�>�n��;��l�
7��N��|S�B;�Wڙ)t��x��!B�©Z��tj�
�Jq�*|�6F��M��[t��UU�����[�_��+�(k��c��U�\k�bl��u�N�]��,�)��Uh��Bs���ZQۚXsT�V�gM���I�d��Mg���Edć�+��E"kE�H�2`8���Y���IY1�<����[����V�Hn�Ȅ?��
AoIA�z0�tv�N�2�
� �
�+?�"2�9�����({��({�Y��<{���=c���+���8n��@�W���t���Um�$ެ����� ������+�}��+�3��Nn��ѹ�k�f����u��w%��eq�Q&�ђqX��X����iS��sB�)����s��N ��R�ZQqlQo��Z�q��1��{p���T&���	��֩/�=g5oJR�n�k����NW�]���Ӕ�kU��V� �O��U��W�Z�b�+7kE��E�(���Xhb���N�Q_sa�[��g�V��h`K/��/K*Ɠ�g:��-QPf�riѲ�@D�G��Ǖ�t¥�H�J�kvys���X�����m�u���,<�H�A�5��]�v�k��{C�g�N�����T_
-�am7(Y��r�n�����dz��C��]��V�˙�sb��c��)�l1��\f��QZ�t������:y��g��0�"N���R-z�"N�ڷ2*O��'O�툗�>Y���.��S���S��^AE�<��MͲ8y�A���e��T�V�e���uZ�gY�<��=�L/O��#O}qg�<�8�?H�����|7�ߓ�FL���v5��S�H��6���_��J�����S�6��Ժ���w�E�������kF�-?�%]^هTͣ;qG�
��
�ߚ�
߆zk~CP��a�\Vo�A�c�J̏�}��G��~};�_.���z=��6�B�T���ΌK�����B.H��J��}���	*}��,^*'O�`ż3J_�~��wX��7>�
��o�$*�,ݢ�.��(��q����K{�I�~֐�B�X��U���j�`_ƛ[ ���a�ͮ�hA���Y��*��+n��g\rC�/v�p(f7�P����Q��|/a�����5�|Z�g��?������?���\��m�?��'^�o��vs��G����`a`���/�5߈��"�d/>��z:݊^.b�u�bP�~p0p���+Cv�w~�Qt�vm�<MʆM���Y��(*P��>Ё��A�r��h�{\�!y�5�@*G�����E�%�1�v�F�3����rҊ��췞��h��R�Gm����vᙉm&��(x��r�Z�HCw&r/�,e�ȓ���0�>��!�6
��=��!���;qH~gb�v��iv�6g���#:-..ǻ�oADwe�M�N�s�\�6�x2�4��Y7^Er;;�ed���?@�=W�Q����d�8�����b^�hd/���ڌ����n9#�TZ$��~*B�6����䵂	��(����g俪�u�5�z
�<?��U�[�j��v�ì�N��63e����aX�\+H?�i���mT�.p)�r���}�Ύ����qy������+�{з����o2|��]]���y_�K�&��Y�a�펿�h�$�'�1���.0#j �W����-�(�W���ѽ�F@!�B�2b�~M>:��QK���s����o0v�&��nR �H�X��2=9A$��i�%����t��d��mǑr���g��"[J�Kƫ�ձU� �+�����ƴ�����S�u$/��@v�	��@9ǭ���g�?W/�Kf)/�=cI����#2D�Щ�s�P��:�$&�*��{�?�]���7�����\�#y�,�}Oql�g.w�$�ծ�~��u?��ѩ_ٳ�X[~*����<�۬��Q�C���{o�{�:n�|��8x?�+�n�ϗ�����s|>CT�t?��?gWƾ��>c�}{x�\�L�	�+b���5�����:�L��R,L�B���H)J��ʘ���^?G�����le|����w�=�㞭qσ��BE�%f�q�f��ߟ??��+��*�y�2��[��x��� �~^����Z��ψ{Ί{���79���я
���q�����N�����������wǛ?����7���u��������Wď�ח+���Ǐ���#�h��������ǿ,~�����w�S�9zUEzވ�SI~'�)��[��x����c2:)RK�d�mcrg?(��#�	�U&̃8�nKN�����U��[�Y����IĬDI8�%��/�Ko/��wZtKcr��BO᭺��TU(I<�,V�o�����B|�cr��&�vr�ݙ���i�n��	����+��nl)�V�26�����Pz]��?Fb,�l����4#��2��v�x���~���������3�SG�7��X�rӖ�[R`~.��T  3��軐��]an�:�=��6`/�vW0-�ek���u{b��g�iۣs왃��Ӯ�J�[��-�g�x��3��~���� Y��7�+B��m��,j�fh�8��= �}8�B`�f_��X�ޖx:'�m���`r��ڊoJ�%�{�����L̥��S��[���J,�G}u��bV��8R�ML�{Kk��Dz���K:#\+ښDyn��t���H�,JsӅ��5΍h�>w��z7�Md����~Љ������lu�޹9�#��z��#"��1^��{n���켂ǋ�r,d��F��GT�<(���q���/��}�=�{���*�����@�{�Na,��U4%�+�Y�q='"�|֔�Z�njj��zb�=�����~���J�����ӷ?�
�7����=�����x��շ�l�������Gh^����I�M�b�'�����~q�O�w�ן���#W��)�=劾�B<d�:)t�/����[�HD �4�6=]
��/%�~ Ä���݄T!5�:�F�:q�
�DI��/v��'�L%|�����������G�)җǕ&W��v^�]�[��I�����{���u�/�hޖ���1��������&�������Ў>�|�������:r�v�9�����==V����7�I���O�D���L��N�_��ݛb�j�|���wp+/�́�>�>Ǌ�:�uQ�酕vt�o,���ZVN��q���ߊ{�m��k�F�#s�L�8A�:���N  �,2#�^/R毅����u���B�>�*��[/��Ŀ��Ͻm��_����cE�Gf�[y�6�RLY,�^����D����To�OL�����Ck�.����1�g@��b�)X�R���̛N�pǵ��۫K'���^z~�����B�����
�ͅسB`��i��)�ڪ���ig�kv��,�� ���~7��Dl	��x����D���H��w	H,O�C��4�Ѓ%��K��#}=��^��=>~0�S&u�����\.'��2�n�E�@yI�H���L�\��=8#��;�6¾a����1�%E߉��E��rW�3;��
(o%��3;I�g�U���>���nzxJ�ge~����x$�����gF
����_Y������R�^'��~%CO`i��m�q�9� m�1�na�tNeƩU��K:3^} On�1��G.�noN�A������oz�yzi�����,�)�T�=��g<���R~}�תz������4	P
�
/�x-z�*n���w�XZ�>7��p�bP}�q Ӭ��37�����³"��=auJMy�*5���S�5�o�zV#��8�<��z����~!�`��R;_I�A�t���*Y19�	�Mh�P�41��o�z~+'蝈i����%�a�ait�ߧ�;Z���K��x�� ��RX��x��6j���k�i��e��s<��8�&�*���=~@�|=�y��A�tr؁*z��_����Xm�����,��JH+�a
��3v�o#�Nn:caq
s�t]ҭ�bc�<��9X��6Q2�A��!�vȣ�hކ.)��S���%5����d�}Dy\=�1��M�)F���{�!�sH�'���&��y��%j�0\���T�K"�sv�I�ʌ��%����<r��&v��e�����	s<���e�$��J	�`3���WzR�r�	ӑ��,�m���&�_�Y�qԪ�DWpf��m���%)n通�����	� �3O�U! ۙ���i���F3H�~���c-�5�����2��t�U_׆yw3#!K����h���n�N���@g�&�Tz,�U����	&���ԇ�M�ʍ��ڳ��Jy(�xR�����Y{���n��$Ȕ ���=��RX��S�C��<�r꾄��= �� ��Xc��c�I�<��o�d'l�%fy�/��r�	3V�Z<�/����fv��(x� �Z�<>M.��:�����<�w�z��	�;F�0���W㩓���K��>�`qL��g� �GB��OJ�sloQq��V�����#Z��_	��3��ӋW�����;/�����דg�&�S����Fq���Q���<Ny�Y���JIP�-�5�kBv��>�?CϏ(K(���9�oi�*݋��NSlݬ��*��*�B;�m$��u6�Q�<����0D����/��[ ���@��'{�w���Q�d�Q��d�%�nFOK1(�������CX~;��i�y4I��i�P�p�1�/v�?�R�ψ���3��`��bi�t���(��212MƐ\���؀I�`�@_�F jQ���Q��4�y�D��te�7
@���(�P!�.�ۻ��BvHw��'�OqRnٓ)eS�8ʦ��yB7�s*�ٳXiv�=�;z%���*Ϯu!�}71���Пe�Y������Z?c�[�;8�EW�w	x+n�)���e�67��x���r�'�\��]�h�K̢��௥
��h��q��-��?��lϛF��l�7i��"'q7�vB�
n;���
�>W��劉���b�[�cc\��0��?�-ྚt�@�?)�4�T.�R�@��-����'��:k�?`�^u��/ٯ}�T��k�:�_Oߣٯ��)zG������T��
��^{u��a{5�>��cT�C��=������6�����Q�����~݃^���1�������w_�Q���X�i�c��/P�ɗ���_��`��۽+j�.:��ׯd�~H�_?�M����l�D���҄�S�"�
N���(m b��=v�:����\Ӟu���m�v����� ^3�Ȼ�K4&�+�5�	<�%�)��R���^�po��$β���M��s�������UDY��YF��ŉ��B�7��D�'A��H��~|��θ֪ E4������ 2�cL�{�s�s��Y�\��oO��-�j����Cݛ�ڒ��ƃnt�kF��2^�
M(D�[@nV�zV���6��/�h'v\e�����i�>������w%N(R&<KA&�:@k<|����}�dEd��(V<`T���o��h���<��_[�!����ǃq�*4�ݦ�^�N��� Z�����l`�� ,��wE��k�&����i��p�'��.�Q��>0>y�Ŷ�O�Q��c6��s��m�};���f��_:Ht�MIǗ�*� 4v�� B+%��4v�3;"�Y�6��}���7�#L���;)��qFXB?<��`Gh"tf�����D��\e��4��#3�+����ʾ�ÿ���׷�r_t�-�Z��mn��[z���
d�k�I(��^:�-�;�����"������p��<{�>�Y.yc|i��6a���K 2/�^e��] "\�S�NҔx�IU�@_"	�mI$���xt��jQ`o'j�բ�n����I( ��ԡ
������-?U��B<2�VbF=hއ�$� �ѷ�5�#��4�9����}.JO�yR��o�����Ğ�{��L_w�����
�&���	��H�Pg1�c$4�i���Yf�]dr
4[�a;C�Et�	D�}��R��D+m�',�qR���a7�Ӫ�;<{5s�w����>9��YSMz���
Kz�t��vǼ�����qwL��b�~�.w�O�a
1*�'��ݜQ���)e��ȇ��-�߯Z���~��G�uO;�ç�oq��l����v�#.�f�6��.����ޅ
Mvs�҂1�"�8��-�y�EwlE�h;/��@)����	��C���'5ųQ����C���Z��L�ID�2a�P�7��qO&��4���Po��rp���K�L�iԃ���qRYc\�*#v�g��hou�BwG�/�}���dh.��������f>0> �A� �)�;՝��uX���?w�k�Q���c�X�v�s�P1��GeA�.#4��{c�39����P��#b�i��*
�Z~E�j�$ܶ����sPg�1 ��FXy5���ZLx/}��ۉԖd��JD��%%=���k�t��p�Q����&m)b}��=͚ܲ�π[��y��t�6V��I�x��aͧ�؀�r����ث�x��v�8�U&�¿�.�ƶ��W���J���V�(���*unNהk��a�*;����<���x^Q�9u�
�ܯc �.n$Z4�ja��a�X�] aIx���P��&��)m�q���I��{V.�(���p����&�Ƽ�9m��a��)T`�����6���#Z��[�^S0�m�;x˥i���ˡ��F/
Q_�g�]{?)�J�R����c��	a{�KLa���AT�p���E�P����Q@R=MN`V5�'}D��P.U�~ծۯJ��`�0-�x""?o�=�V�'$�.܈1���Ճ

Q��{bp��>1�׸3�x	O�x�:���R���9HI8�͉HK�"�#���e��rGΪ�u�A�M�����Z��A����H$���,@���aH�V�B�1bG�f�'�ٶ��D�寈�¬3)�hXSБ���=xI���[TݭV?�!�s����x<��J���f�@�Lf�.�B�P[�Ux�&��p�,��s��_A�����NGwuf������|�ӏ8�S��D����SHtc�r�kN�!�e�/����F�CI�R�H�X׸!=��`�[ߑ��w
K�Dv��Ǵ�ii墱1�O'�lQvl�P%���]+��Z�H�*�o�L&6�c��JX��?lӐ|o��H���Y��4+�M��&�5C�Zy1�'��0�o,�n-:�:��|�A3;��m<�l��dW��y\;�^�\�4�v_���5n
��3��{�~Jx�(�;ՌN��T����ƗA�`�4�v�h	�mW��"�>�T�^���_����=���b!1�[��h{��)J���=f? �����w ������ϳ�f��F�E. '��c�թ㮐~P����^��4ZX!�[� ��\�]��3�?T�,b��	��B�;��9Ű��?$�F�5�sr���}�|
ꄆC9̓=�!���H� ��=��wǰ���rf+*/#�}'�	�w�@�
Db#�����J�4�ϔ��@���n�y03X�{�����!�ɒ�-��o��Č�c��@�s������0�ֻl���X?��{�I�H�������?0�՛�ݜ�*��M�ʍ����@Ӡ�
e%=剥��~�� �����99o��<*�M��-r�t�yF�6:��)e) ��m Ќ���XT�6`&e��3��g����83�44���H�G6���j��/�#���6C�~����t�F�/e�K�e.�1��`�D�+�h)�+_�g�5�/+����h���ڰ	.|�p�e�8^x
    GTEST_TEMPLATE_ T16>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates16<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates17<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT> {
  typedef Templates21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT> {
  typedef Templates24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
      T27> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT> {
  typedef Templates28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT> {
  typedef Templates29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    T30, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29, T30> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30,
    GTEST_TEMPLATE_ T31>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
    T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
    T30, T31, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT,
    NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT, NoneT> {
  typedef Templates31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
      T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
      T28, T29, T30, T31> type;
};
template <GTEST_TEMPLATE_ T1, GTEST_TEMPLATE_ T2, GTEST_TEMPLATE_ T3,
    GTEST_TEMPLATE_ T4, GTEST_TEMPLATE_ T5, GTEST_TEMPLATE_ T6,
    GTEST_TEMPLATE_ T7, GTEST_TEMPLATE_ T8, GTEST_TEMPLATE_ T9,
    GTEST_TEMPLATE_ T10, GTEST_TEMPLATE_ T11, GTEST_TEMPLATE_ T12,
    GTEST_TEMPLATE_ T13, GTEST_TEMPLATE_ T14, GTEST_TEMPLATE_ T15,
    GTEST_TEMPLATE_ T16, GTEST_TEMPLATE_ T17, GTEST_TEMPLATE_ T18,
    GTEST_TEMPLATE_ T19, GTEST_TEMPLATE_ T20, GTEST_TEMPLATE_ T21,
    GTEST_TEMPLATE_ T22, GTEST_TEMPLATE_ T23, GTEST_TEMPLATE_ T24,
    GTEST_TEMPLATE_ T25, GTEST_TEMPLATE_ T26, GTEST_TEMPLATE_ T27,
    GTEST_TEMPLATE_ T28, GTEST_TEMPLATE_ T29, GTEST_TEMPLATE_ T30,
    GTEST_TEMPLATE_ ���i�_m^?
�+;@�p�ڛq��y�QJ�`�k�?�jU��՗l�/[ɜe:¾�9	����L����k��)~l�T1�c6�m����dv<��c��.��U&�����U�a�1�*�0�������燐��S�Y��n��g���U��,�X�,�RU��wv[��m�qr�{��l������}|�/��U���`ǮlU�����n�c�XءZ��)!��	��6�oϟ
��B)�F'L��#XI
���¸��z�7���7>5���G���E�.������-h��>{����S>��C�nқ�כ��D�\������OH����y_j��@�
R�zg����>�O>�ox}�����
QՍ,���
�#�N�.��$ס���ZUe��O ��]��5f�hveϭ��i`�[��K���]�y���zU]�,��g �C���>�������:9.�۷���Xg�j�s'W���,j�G�c���ݠ�ѣ���.�;�L�PH���o�׽)���Q�S�O��Y�G$��F�󟀷X��?����3���Y��<�	�:�p�z<���8���l]��]��֧��u��~f�z�yM�ǣ��"��D�x�߅�Z�D_EH���ߛ�<��z
�z����^=����`=��z·���
��0�m���C��ѠyJ����T�A�U���e��NzyZ��L]�R���n#�H�'�����S�E��?y���N'5Q"�/�Z!H#��Y-ݗN�DK��'ۣ��IK�����.��r�eidM,�ӏ�K7�6���#�� e�D����;�W�ɧ�i� ��}r y��^a� �q�؇���n�&)��<��B ���$�����0M5��ܿ��n�eА�u��c�1�W$��Wt����A�����_�ide��@�9�?vY:y$n7�3�W
��E*|C�����n�IGl��r&"К�o���N����~Pu���m'�~�ON�<k��z*F�:�>���-E�!Zz�I�F��r���V����E�*��+�卑��$m�!/ƀ�c1n���eN�3��l�9i�8�3��$�J�|$�pV��2sꚩ¤���QQ�!���|�@��D	k�����l�y��I��g��Q>�X�X�������z�A��q��9t��6�
�!�Ԉ�K��A=�"�"�xr,Jj�%;�,Z�Ңr����Q% ~*Z�����";�/��#�b�w��)�.���X�;YP;��,s���S-�9)0�4|aG��vd���,�;�`��X�2���b?u1`��ǿ\= �\7Jj���,�v�L��"�l҇Q�����	��#�Q�4�"���"p�ɀ�(v�$
����@�{Qz\?.�3�WK��ad�D�6�l�F�@ؓ�CN�s�~����`L��{7E�xE��%
���"��Q �+�|���t$�9�c�7�8�_����c7B~��(>֝��@?I&/vzU�4���L׏'���w<�&�gǓ׻���|�A�t(dk��eCw
�{�������dՅ��I��t�$roO�Ti�Iw�ʋ��"���."�R�+ɪ���d�%t�D���|"y�RZ7�l�Mߜ@��M7���Нȫ}�����>���˷	P۩�U�iy�eO G�lpߐN��'G�&���Ț�̤'�<=�5��u2����k�e1������,f��,�B�0���}}~<Y>�IJ�D�J��9�>��	dI.���2=�r�Ա\�gi��"��k)�
����'�����o��	"'/r���Y�\9	�o'W����wf9c>W_�w���	�����xc��BO������FN�ȧ�����,Wl�����)�!��͟&l!�[�0������m�w����{���9ԇ�����?⺐�w7����j<��K��9�s>+��>�Q�5Q�~�ߝ�y�Hݞ�F�C��f,O"�9�So��'b�3,��d��f,;>_��S�l����1Vl�kwD��7��G�ɰ�Ќ{.6�y.E�Q\}>U����x�?g�Z��s���/|�I ��������v�U�`=��b�؊t����t��H' ���v�5HB��N�{�����g��&a�H{!MG��tҙHoGZ��!���D���H�@z�
� r�A�[�䍼���En>2�1�>Kf�\`��ߠт�~��98����bЖ ���ж��̠�|���h��(?��
����r=��֋��N~5�
�E��.��\\V"�n���4����w�������i�j���7��f��������x�����t��y�̙��k^󚙳�(<�y�J�����T}L�C�W�v�	�����vB[��KP��y�Zv�_�\8�W��|e����QL]�Y�=��l�+� ;�{���V�Q���� A~�Ju�O��kD��
����Xx�������8|�R��dgS���a���_�.:xyC�;���%����Q�G�=�zو��G�:4@��7�
�T� B{���TPw�*��fLV��>��
t�ȡ6���)�,4l� ��,�����0MSRo�^�U���<���<rrlޯ	�`ѩ�_��z��� ��`��:A��2�J��h�Y��)t��*��BR��*X�To�"]�P���-VB�ad�PO�j,�N���^�j������������B�ū*�Q�Z�*���Q{yh����BC�o_�Z_R"�t�����	�~����F�^��4h�8 􀧥�64�g#c����2l��z��`�[���m���nҖ���c���gp�D�s<�b�|�n8�Dy_1��f����[8�±�~��<"�
�_P>��_�����p�G�����|��a��8�|�����p��u����M8nqy��\߆�.^�������I��Z8��QIÌ�k��p�G8��ہ����u#�n��õp���)�p4��s�%\��Ïa��
�5.�uF���p��m����.��^�gأ��?ԩ�	�
�=O��<��>ՀI��irc�����Z���s3�n���s�P��s���|�v��=��I�����3�p�GW���;�{�u/8���xb������
����)�Ԑw�u���Gi����Y�>F����C�>���@���ӳ�:��Ʋ9I�m�߻���9��n����O=�~sxf��G�;N�m�� �`Zd�_�[��6����	?�꺮��v�_���3`ub�g���Zz��7��ݨ�-h�լ�����'~c٥�>�e;�����;$���m/?�~S�Yf]��K\��������vw�>dF���o<ئ�4�U��?N��{��&S@��e/�Xӿ��o
�1�?b[H��-s�y>[���i敱�3Q��;�tWӱ��ꭙ�^�u���ƃ9	/v��{Ϝ��_�~k���f��̱�+�\�էo������%����$�x�Ӎ����x�w��'�;i���.�y�t��K��1o����X�������|�풚�c��N^����g��iۖ{u^A������m6[᧟���b�	��|Rf���w�\4g�»��"~�og���Ē�S������9]�^y�����<F?���6�{�[>�������o�����^
噯��w�}ۺ��[!�=��C^
�Q��=�{N�+��|���+��9W�8������+ԧ�{�������>�y���\��}��=���=�V(�x�r��`�ʳG�ݿz�=��.��圂nV���g+���B�{(�{s�<F����Vx�B��V�Sz*ح����IA��
���������=�P�K�
z}�P?�{)�/�z{U�N�UH��B��
�vT�/��풂?���.���B=oR�/������y[(S7|�B�MV��
��M���۷t�~�B=�P�?�*��x����`��꿣�=(��K
�<��Oc�rV�vϛ)ُB{mU��� �xi������f{X�P��
����{nP��U��~
��R��q
~�[aܟ�����h�[�Ўi
��
��Q觵
�=���Bⓙ
~c�B;^zB�N��&�y�B�
�'Y�-Q��*���
��O�o��Я��?E��*��L�|��P~;��`o�켗B=G*������B���gz(��J�v<�P�d����Pa|��ͺ�M��E�v��0�+��n
v�]!����ո�+�{7yn~�I�Z�cE>y��{8�it��	�W���H��yn��#�M�7�=����,�_*���/�i��y�1��ȟ�/���b>ͥq�����"�i�ڷ��E�Ki_�=��
�a4��:�wC����q!ǅ�R9�?W�+�χ�_Uq��!�[UK���
��n�ܮ��~����������A�O�^�a������E&�����^���^�I^���~���O�����~�W�F?�f�U��W7.�E�tV�n%{�B^�`i=�p:�0}���c��E{�*��װ�pQ��;X�\h���/Y�x���0O�"�!�0�����'�U1�g��?`��/��Hk0����~=��2���5��1�	l#G|�]J���'�̗���ØV"�~�T��f�x��Hc����7P�=�WY�<�.��S���K�����Q>?���L��bz�7Uqܑ�'я�E�&}�]��{b��b�5���S�?�~�T�qK�*1���,���^�y�l������_��?��WI���J㻴��Ezo3/B���H�>�^Q��Z)�C���i_i]ǣ
���������]��c�Y�V>��j%�p�����a5����Xc�y�Z�K�	Z���r?���P���؏�-b>o"?��[<X�K�b\4�����#���[��DK�]$�:�a�cz���?��
\��~�t��=��ݶA{�̔�?���K���'�� �?�������<^��xLZВ��#��%\ܲ���_�8m:c/��`���h�%��R>`����Ǘ �3�-��?	�y��<�++��ρ�WT�\�B�o��z��x��(�Q���>��W��3��	O �ຮ����T5�s�w���c<��\+���g0���>���*�ϊO�|��
�xO�ga9���y��~~M��^����V9����\|X��2�}D(�I\7�*�zC�b0}�h�ӗc|�]���
�U1_n�+�x�ݸ�(|�㵅[����P^�}��z�|��x�u��0_��)�ӱ�v��.�PU�緱�����$�����~]Z,��a��?�3�#?��s�훀�R	Λ� �F��ϗ�[C�/�>��s#Η��J��烁ܾ�1����Vi�Q�W�����8>��*o��h�Uhϣ�݇I���ӷ����:̧�^�#��p?�Ê��|`;Z�u�mhWM�󻟰�1mE~JO�b�?�B�������p^P��#i��!Ňoc</��H���^�|m:����_'���Ѯ�����g��\�ϖ��@��K��w�����{�(}O^��^e�>ȳ8��P�I��E�W�~o�Ԑ?�|&�w���9�<��K�Kf�N�����
0}�N��,�#�	�}Uo�+�x^�߀�`��_�[�8��o-_?�,������4~u����W����$}ׁ��Ow��}�*�?��z�r�Dz�Q���VҼ�J�.�W�w['/�Fi^�?\<#�ڿ��[!Y�/�u����;��J��ؑ�`�)���������Q��3��t��}�+����R���a��ř���VM����8nZ�ʿ��v��'�ΧV�W��K�b��~�A>�yG����|�ʐ�����Ӥu	n|�!�S��q�Oh�1E~ ��w�~���qV���Y!�﨤��O)N�h'�/�3��C9�!���^��[���4[�>��(na"������������2�����H����x�����gF���2�߲R��{D�g�����D?��+���'�&��)���V9��߽���M"�B��������h�96�-DG�o�4&&����񣇧�����H1���߉�ˎ�NHN�MI������0��X��h��s3��qD��0gEg�f�����3�L����ٱfctzB��H�d�Y�i��	�	��)�sb3Ӓ��F�9!8�4+9�ym�L1�IR����)����Ғ���IIRcSR��I��,�1;�Y$Ɍ�YN��F��t�:���͢�2b�ӡ�b�R��1������2U��(��4'C��M��Dc�1;#�IG�m��L� ���'��w��P��
c3c3���Yi�s!}zZ�1:9-�
�T[�,�Ct��Hc��fNP҅�3ҳ��n}���.C�w�<djr����Õ�qE||
���<W�Y�+�avlfrl��qy�G��crb�c3y|
Q ���c��\��z\��O���aJO�������ǥ��mv���mM-"٘oRJ�j̄A��v��������@�UJ7gͤ���>�%�G���_ɊMa]H\��H܇B��X���L���q��Jui���+�g��'e%JW�xfzr�l�a��+����ěӁ<&}B2�����NOI�#3-��$�F&���D�%E&�a҃������+��%�){�M�a�����萛�'�,�` �3�7�q!6��0���=� +�ā|ΘR)ch��ǱwIm<�6:���ɩ$ܧ�;�?6u|rb����!&6f��6#ݔL��S����f�A\�����,�9)3=+1�?3��v�9{�ڈ��/N�����xn���<�R7O�A_l���������2��6d�(pÝ����in�9�H�<�m��j�ߥ%�܅wb�S]!�,��d�9����b���*��=���@�@)_�%�Ŧ�Fj�w�Gg��Qp|����;4	;3t�����rn�������W0G����i�U�2�X���H��W�{'ÐM�f&�f!47��)�鳜�@'� �L��An"������l�D;?A��,2m�xB:h�If��2�r��B
��ědD�0��PW/{qh�_z��.ߨx#F�L7�a\�co�}>3�T�j��ԃ)bXE|�4	b!C)�N:�ǚc��f!yJ8)�~����k��4�c�)I������sg�S�n��i�&��� ���<��I�n�].����~q΅�Lc*�0p�6�]݈�$iΝ辨�*�����z�(е3#9>Y������������,������xb$)0�O�����i�cFs�$gf����|���#�͘�Q8���l1n���e���W�lx,.2���b*�J�J�I���k
Y'�v׺�<cf��)DC��=�����)��}�q��&�Λ�����;�ȝ0��7D������(S�T���<��g�\3c�ȩ��8u���YRg�Y9:$��"+^�7�A�iOk����&�<��'_ofn�l���F���2Zl���H��;�%skhԴ�$an|�p�U���@�zml|��n�]���|��D�H�39b�!��!��U�A^p"�3�����5���֛s�^�|�c�n��%�`�|8 zd�����
��n��gR��R�V��-��O��H}*�i���]_|���ݴ�'#�SR�3�~��p���X2�$p%�0�p�A}{���{|���H�Y�1q�$.Θ"ێ�	�s���,���.Fck�
f�j�H7�S��hy�Oav�^qm�����-����Ӯ�lβ�����py��k�w�oF8(}�a���^�7#�W�M�X�RbM
�9WC�F�XQo�@�ֺ�+�'����u\l�����&z\��K��w�>�}L�})�C��SH%WO��s��;q�;�@���,FDFݯO�>�o�GD�	r���ο�!�����s����������!���,k {����p�� �?^n�?���������i�&'������߿����Ё���[V�do�ò��U?���;Z��s�����d��&t�V-_Ӏ��"d͓��?�e�y���+d��-�����q�z�E?a�x�j��k8^r��*9E��x�O��k������s��G��<�c�r\@��Dʗ��/��"��ˏ|_~�1|���<�/?���ȳ�����͗�f�W?'���㥃E����w6��PȧR!;ǋ1�j�g`>5�B�Y��<������}y�)���O�B>������x�3��:�I
��P(O�By
�)V�g�B>�9�W���W�^_�~�S�P�J�����J���2�~��1��Y�`?k�g����q_��5��cP(O�By&)�'����0���ߒ�q���+�g�By6+�S���n�|��PȧR!�B>�
��(�Y���{:�K��qy7�|�	V�ǰֽF�uo��ֺ��$�|2��Vȧ����w��9^!��^�~ֺ/J׺/v�u?^���ǿ��q��W���1�Y'��f�sD�W����o"���N�1ߋ<�㧐gs�7���B^��G��q���o��R��A^��g��s<y%��#���L��7!��
�?D^�qu���B^���ȅ�r���パ�q|�n��<���C9>���K�O��r�1߄<��ȳ9~y�O!/��U�%��f��,�v�x+�e��O#��xr;ǧ!�����A�#�p�M�~� �?�� ��>���Dn��y�Q�A�q+���A���.�-����a��q|����������8�����!���J�U߄��� ���A�w��r��B���Ȼq\����qo��<��ݐO�� �IA����-�����)��q܄�����K9�:��y9�7!���Wȫ8���㧑�p�r����"�q�>r?���a�s��@�w������Q�'q|���D���L��
�?L����1Lo�x
����5L/���]��^ߍ����.���q��wo�<�㝐'q<y6ǟCn�����:��sף8���+8nA^��<�v�oG^���ȅ��|�n߉<�=��]�?��
�G��������������r��5��ۋ��ޟ��N��2�1}��#��x!�$��<��_"�p<y1Ǐ#_���o��#���a;r�5�r�D^���ȫx}�Ws|
���A��@Η �q|#r�w ����1?�<���gs�r�/#/�x�uo�ۋ���K9�yǟA^�������(L_��wp���x4���xr͇�z2r�?F���b��8�	y0�?E���ȣ8~ �$������!/��}}�p��ԎoQ�����ȫ�6�yL����~�ܟ�!��'�g`��M
��gc�$��C�����1���!/�����q�(�r�W ��x����9���.��k8^���ܾ$��q����w�x0�@��E��)�
y��F^��8>�p�L��������!�e�y��@^��R\��jL_���_�H�=��q�r?��E����9�y0�G 7p|�(�OG��X�Io��l��1���q߳����~��}��ӗr���X�e߆��9�y%�"��x%�j��E^����j���ߘ^�q[6�;��0}7��������C9^��$�w��[��g�C0}��#_���K8�����s���x�r�/G^��M�5[9{@��xr��#���ߤ���%�����Eq�.������(��e�^[��w,o�����O��xoL_������㡘~�V��r�Ga�
��Wq<�}������az�c��Q:�����>v�Ս㥘>�c��Q�?��
����s�b�o���o��2�w`x9�_`x�_dx%ó^�p+��_��j�������p�R��_l����g8���nW3<����ǂ��^+�����fx�1|�3<��>Obx�g0�	�g3\�p�u/`xS�3ܗ��ތ�%o���o��-��X�exk�nކ�[��e���X�ex{�n�$k��g��Y�ex'���xgk�pû�����3�)��ލ��wg��=X�gxO��ދ���f��}X�gx_����?ÃX�gx?��ޟ��`��Y�g�Ӭ�3�����?��������3|k����������X�g�P����?����3|k�;\|8k�c����3�y��>���X�gxk���?�G����H��>����a��Q��3|,k���?�ǳ���	��3�%��>���Ob��Y�g���>������?ç������3<���ǰ���X��>���Ǳ���x��?sq#k�O`�ቬ�3<���'�����3|k�Oa�ᩬ�3<�����������
k��d��&��nf��Y��3|6k����?�����y��3|>k�_��?�����WY�g�"��na��9��3|1k��e��y��3|	k�;]<������pk�_��?�Y�g�k��3�������?×����b�������d��X�g�j�������e���X�g���3�-������o`���������.k����5��Ы��Y0䕙�����d��
WD��QU�ty����f�
*� 2�b:ʨ���dj�(��b"�)�����L���b*g�L!*�$2)�#��3�L��*O!2�B:��<��d����H"�)�#��ÈL��*&2�":tT�Gd25tT�Ad2%tT���uT*�!rS�?�}��K��r#"7��Sك�ͩ�T�o�՟�7�ܒ�O�+DnE���"�Q���+�[S��|��m��T>J�T*�#r;�?���=՟�;��$՟�[�܁�����ٟ�O�7�ܑ�O�D�D���R"w��Sy1���T�G�.T*g�+՟�3��՟�3�܍�O�)D�N���8"���Sy$�{R��<�Ƚ��TL��T*�#r�?�{�/��!m"R��܆�AT*��՟ʍ�ܟ�Oe"��S��_ ��S�&����S�
����S�����T��ȃ��T>A��T*%��?���Y�?��9��O�D~��O�-DJ�@۟ȡT*�Id=՟�+�<��O�DN���b"�Q��<���T*g�y�?�gy՟�3�l��Sy
�#��TG�T*�$�(�?��9��O��DM��r?"�@��r"���ߧ�O�(�?��y,՟ʾDG��r#"�H�����S��|�2���T�I䗨�T�B�T*_ �$�?�%�d�?�Oy
՟�G�<��O�}D~��O�=D�F���"O��Sy�����h�9��O�7�K���
"Ϡ�Sy)���T^L�x�?���H��r&���T�I�D�?�g9��O�)DN��Sy�gR��<�ȳ��TF��?�9��O�~DN��S��ө�5����A��r"�B���/�3��TnDd՟�D6S��|��YT*�$�l�?��y՟���M���D�K���	"ϣ�S�(��S�������T�C�T*� �T*o!�"��]��D�P���&�s��T^A��T*/%���O��DΥ�Sy���T�$��?�g9��O�D.��Sy
�mT*�#�R�?�G���O�aD~��O��D.��S��_��S���Q����'r1՟�m����Oe_"���S��WR���A�UT*����T*_8�YH(;��o9;㶢�����ȋ�&��l�֚'f��pn�91��VW��� ^v�~�%��vȕ��>?�M��Z���ZO��ڰ�>Ԡ:d8^k���l������<��%d,�#d=e��$������P��=4��?�yu��U�<M��{�C��Ǝ�R,7�_��w�,�*��x�^?~��
gjy�
Å��b ���4���1�dC��Dz@~umXe�m��v=�Vn���4��������n�N��y���-,����3��h�`�B��2
��W�;��T�Y�/�����z�/v@-���pi���Br+�ʇp�`��2O��'�.��!���ű*�r��)�4� ��o�\��h�^I_�������o}�=膡��v��X��]��2��1��B=��3�i��pҮ�gPU�O(v�̋����I?A?>��*�vҐs���Bu�l�~ ��q�PI6u���:��� ������k�D��h�%�Hs�"�R���Ak��j :�a��nd������l��*�x(���}t}��:�vW� ʨ����G�鈢�*���Bd��9������l��K&��5�L!;ϓ�8h��i���?����<������?�o]]xޟ�Ea�W�:��O\�jh�}*�Oa�~�ϋ��tЬ�߸UW9�4kH�n�7��o�/VW�"C�R��b���������	l��B��C���I!!�HۡHR��Q
��J,�z�N�KRX�A���P�9�Wyk�� Q��#�{��ݶ/i������"�Z�u�L�F���!��d�a�.�cnj�YA�=.t������Y�͛��=�Nہ.��Ϋ3_�(j�LĠs�ߠ�;�%�}�pX �n�3�΃Ƨ�i���܆ƶԋFM����(/ L�Z�	W��J�f����vM�fo�}Σ ����ͧo�d��]�����cv�0�=`Q��&��͟C�D,�ޒ�� ʦ�6R��jsU*�g�i�^,ų�HU���ۡ��U��\����K!!��eaێڼ���@Ga��͛oʹ�ğ\�{��u��+�v��J�7���RC9�l)j���@[j]�Q���ֺ�����og:������ x�S0��撿�2�^F��hw�2X���>A���#T�i6/@6D������ ���W����zp�{m��5���;��}r�!�����?
h&d����kԐ�������v�'c�]�x�o ���dm"L;�j7Y~�,\ �d�a��eC\X@���r@ d⇮B��<��~�aPU�e"<�e���v����z�g�	ѽY�8��������6���d4�H��� E��j`(�5�[�
�P6P[�;��i� ��c�Ku������[ԳA��r�=g�;T�7�L��P��E��m���{^z����G^���g�}��Q	6��+�}a�>ua�*�>0�B�Az���E�/QK9�I|ق �ޢՀ/��
�U,���kW����^��]a}��V舋���+Z���!�y1�uU��Z��|:�A��=סs�r�N ��EKh&�L������
ݢ�v�>�}��@ � ��<u]oIT=�, ��E�[��^��y6��(w�'�`
FC�Q5$�ִ�.������K6j����Z���nD�k���XY���8*���hXe�S/��4׾~<�5;�MJ���p�J!8�	Ӱ��v�g}NmX�v���$�j˟�BH�4�	9MNOA}���U�� �$m^C�s<�MVT��ۇ����xA$T^^y-g����j�6����'��P��C��W�
��A�'is��I���{Ec���b��:�Nn4i��^���жm���i@�Zdu���]�*�Y-$^�/���)�>�=�#��g �b�am~Cھ!��~�T��.��K��Z�@_�P,?X��ͺ0[@ ��J��$��j�z'�y$� �^�V��*1n�6T�>4邀vĘZ�Y�35��r��v�p���}`�~ڼ7T$�vsZ�`;��G�g����Z�H�?����.'�&uB}��wiG&�M&H���d�Fw�Bĕ�����]96<@�m}�]L&j���%BҢo�a.�?���a��2�r�:ڒ�Z1���\�#􎎗i�Xᠽ��%�;z�iO	�e?z��h5
���ϻ�t�������ڼ�`!�/8��eA��߻�X�PL��%{p��ޠ�v�`���?UBxPٞi����)> �jqdc-������<ڑ�� �s�J��2��ʓ��Gb$�{އ�8S�����@)s�&�
.�]��Z�4G����'�#/�������*���\}���}��{Ek��A�� �6�k�l?p%��ŵp�0�4���=�![U$j����J�x f]��2NᶊoI�7���9�u���{\�:��v<qr���[ [VPA]�}�zBE�ԓ��ۚ,@�y5t�$�=�:�67��@=����ı{ks#�ł�(u�/���I�^tvCnh�yy�Mއ��pE�+h�X/<�ՔQ/Hhe��W]���P�^D
rzY��D� 4*Lv��C~X��m�h_�O/�]H�F���>��}W�d8s���*WNm
�u�����ă��x�������W5R>Ekˎ��<��yȰ(__W��'��e����ܵ-H�
٢��� p�:��oC��k�A�
�7�S^��O-<�E��Zk����u��b�Ӑ����b��8Vᆼ���������T�C�A����M~�@���͈o>N<�8�yܣ�E���=�RHף F�ȹBbr"j����r��o>���2�9N��.y�EL�dy
)�)��)O�);��Q$徳���xA�Lֻ���8"�1Kν%�z�a71M�(�"YZ�vc�vq>�s\���S(��\7�n9D,��SP���\=�A?��}�v����j~���.pRG�!N��?�s��Gt�b9�
F
��`�5�lG�%�!����E-��
� �+�����A���8^���7��#��'H{H�l�9�*��7�j��Aт���;�d���Dl��2l5���	��
Z�;ig��=�q'�\���k��� ���_m� ��ӏ!Q�� ���֒Ş0x1Y�E�H�l�ɎQ���?�ʹ�Cmۯ�?P��>�-R�b0�J"W��*�\�:�w<�g��Ddᙬ�h���T�Q�L_IV
"�*� 7�|�w8��W���7�w?EB��A07M��Ĩ�U�~ח]�V�B+�.��.e���^T�_���Ar�GXQ�*��\��?U�T�0�Ov�o�"!vҙGA�T�����{��o�%X/<�U�@L��^~Ta/0��m�U����2����{/����d	T�p�9{%��>��ZT8Hؠ��eå��QA����r�'��.��7C�p�����Ǩ�{ѻ��>��q�-��'�ޜPl(lX8���0JS8B7�|��WM��j�]e(���^n(j������H�.��"���{<��
�^O=_g�i��ǭ#v�ͽJ?Z��~R������S��-�0Fc��E����P	z0������y'^�Av�W��Xa(ҫ��,�:!������ެ۶	��N�ͫ������i"\�Fl�J@܄$ja�ن��j'��
eӪ��"
n�P���Fy�u�놻�]�Q�P��E�*��"E�"��Yf�����?�G��y��n�=��̀���d��$}�*�:����a1��%U%�# i�X����](��I�F��иoY��G:��=!��{œ�[�fR�<�����<<�o|@��EaOG^x)"�9�������`vC}Rs�#��b��-HX��)���(p1a���?�ɚ{q��"��Ki;n��'5◣����5I��F�����g���հ�E�.ީV�D��|؏���P�m2/���xB7��y`��H*�QP�!*R���\e�*D�"ۯ멷 _��=�j|�0�Uf%
��5̅���F����|@tu���.
�8L���lLzv�*�e�Mr�`"�Y_cK�m�Ҵ ����+�`ҿ�E��V��f2F�&�ࡕ&`F�&�� �,�L�)b3�O�Hj��^�3�"Wb*��a�`]�u]��z�l�����`��JL��Nq��j�ؐ�93�8(?�,l(Op���O�"<���O�"<X����?L���2����\��l!����HU�	«�����:������|��+�����f%Pk��8�ٿ��\��{�i�2�D�(1��4MMb>�nZ\��iS��d�PY	����y�J� P�-/���Y��N(�"m����:��I��d8��#7 T��QïHXX�q�U۾
W�^yU���	S�z�
4G�I����-��6�W��]`r��_#X�F0�5qXM9L@y����!�}����%ڥ�?#P/)p�iK��xA?
��q�=A�I�|G�J��w���
�^P�!Pc�߮�^��j�U����%�r���'�qV���+yE��"�M��h�Lx�Z�����=�<YY�[O������8<�9��뀲\�v{�F���,�ـ�߬�JN�'��F+�H�jW�!>
��YI�	�4�+=�V��<�܎?�G1ʅ;���{�7t��!���CX)_��v�67�YԱ�wE�%�s����o�B�Ptm@�d��>!$�qra��7��a��	7��d}ʿ�)�nŋ����p_������%�bH�\98͖�lvI@���S2xah�1?I Um�:�L��ݖn�2kYYaC�ر����c��e�����Q���9X�·A*��,�[b�����Ÿt3���cy
�y���V<`�.�4�nW�"������R��w1���:�
E��lH@����xbV��6����/�}��?���9#���C$b�@���	��x z�E{������1�-���%j�8��L���>O֖,g�^r�He��1}v��>�ݎ�e/�&\f�w�jQ��o:�]�����&�C���7���U�b�w|d:� ��4�
@�7�2�b��X�$��b�'�-�$��*n�~�!ϦO��)�e�`(��Yq�Okס���4���ѻbxwiR`x���ȗ�x���?(
,�d�dQ�O~��+<Y�)E���]�d��K���S�v�wGߤ�	��/,�E�B�(H��iJZ��_��ܭCC�T� �e�V��|w�ӡ�f~F���Z�{��>�[׿������7}��>���d�b�3�Ϋ����I�ۧ���أ4���=�
�#S�R�ud�cX����ׅ\�q-ա�ؗ-�GÏL��{�ڴ�j���.���\Z��/��|��Q�#���z�|�s���듰0Pp/���5�;[��K�~Y���X�����^���5����r���9�ܧ�D�^�8³�:��{�U��=z��6�6�C�z���8
-�:2�E��D=�c����:��o��w�z��&uD�cd��K���Q>:����W���8�'q�#oE��%�����m���?����.����=��c�ƈ�����[��(������Bʊ�c�a���$�4I�-Un�]��'ָB�+jw&e�qV�@����B�6yhJF����ʍ���͡�O���U��mZ��{m�%�;��
m��\�Ɛz�zu��v���������J����������	��-
�>V���.�=���?320&�{�RӌR^�+n��P�+���f�>�Kl�ʁ�H1�;��&���iy���i��C��ɊZ�%|�+�	S�p�~E{W�!��|�+�?a�}LJ��%��=�#��O��A����UB�]�m����d�����h�ǣ�1i/����?��-��]��آ� ��$g�(M��Ip'��CMf0�Q|Yq�4�������� �r��6ø�\Œ���s�W���}\}�kr���K���%���1,w1���7F���ɞ�Xλfq����e�֤�a}h6 ��(�j0v��{�,�����'��O��{�w�u ��0Z�j�A�4��Z��l}/>�{�ޢ���t?\	���
Ҁ�A%�K-�B�O1��$�>����= �Z���t���g��9�?�����m��������9>e�����^	��<9x'��Y�>���^�� �a��ٯ�A�ț����h��t,~5=I��6�1�O��_��U�N�G�2/����ӽ�J�@tQ�x����O�`'.\��

��_�G�r�������Sl`�{O�����r��zyr�y��r�G>���{�����/,���Է��jҨ�b�.�c1y��1]���k$�� �s�-|���s�u�|.f��Ӻl}�����JK{��V�l�k�u�q⪢r�S����
�#�(O�~|�ޏ�к\��NW\�F�����ti�m���Qjċ
u�����t�v�=�c���ly	?t���.fն�E���Ė�����

8G5�uh5��5�9�۪ G!ܩ�'Կ�vO�����p[��:��O��4�_[>�f�����M��3��#�U���T~hq�]٩�T����m����l\��������M��L��s��ii�
),�c���aJ�%�����B�,
��B<�e�i�䩃/���6�Q�&�'��J�(L�<��=�	������'wU�=.N������`_\�/&<��FC[���Cv��N3�C�/f�%Ș��Y����������O�Ó�]����Z�f�KOc�ms](�%"t��y/�1h�ϱ�Մ8�-3��ۋ�]S$��KR���1~�%�J��l(4�-��d��hUR!7p@���
�:5==�_ˡi-,ȃJ$�Udw����C�*/���ҳF�����^q�H�w
�٘�k)���{1�.�'�hI9Ձh�h�^���(d9=>�1�W�X0��K�CD��Xd�hv&ΰ���:.9qLzQ�,�&1�L��v�:��˒�[��4uɕhf��2;��fyDc�,�����ݒ�(J���WN`F=���g��(�
���Z�F��aG�T�VGX\��44�v��Q�Gn�]R�KZ�7������X�+s�[�)P ����c�<�Q:&չ���ٱA���<C	;��Ĭ"�%��2�v{F�t<b�z�G�U�A{���>�h�4�rEiA�`Z�Q�)8?��L�	�[�ar+ƽ[$V!;���N��%�Vn% ����F`e��)r�UCI��q��і.e2z<i�<�$�
U/~��bh�0�bD7����Zx[z�jW���6�?9��G(\wj�E{a�ة��;1�\��v6����Չ^yyr�����fXh�Ys{�>u��2:�����ҷ��3������'�!Ցd����4l��d��T��7%�7�g˕	�=�H�$�0_��8':�9� ��}*���.W��V���&�ץ:�Hr��DڧE{��Oo��uv:�ȏ�FϷ����4�|��/Z(,�F{�'���8�J�<�(�Uf����8*?2�<�u:�v�OLI�8����WB}�Q���#,�H�m֬�����}�WZmo�	�<���8�l2��:ŪH�޴=��1Iw���2��ֹ�7����i���9FW�����գ�ֈ�
#�~I^�~Q�
�����-#!'he���t���.Ϋv�zU8Y���BWz��Q.b��_p�L��,ڷ��������+(�@�0Cөs$�.4��]��S��e;ճ\�
C)xᖽ���^տ`�/�WI���G�u, /��o�zQ32���WlR2��=?"t�sfoȇK�{MU���)�7��P�
�P��~��I�͇ت�1X�#XE���E ߜ�.��# ���v��'����e�:c:�ȁgi��=g&����U3q���/p�q��p�I���86L�84η�"jg�&����̽��F��蔯���4�Wll����7��=N��Zߵ�����4�/�䙈����}�$W��
pȺ@5��
G�)�i��`�K��?���5���)�B	L�Ҭ6�o�~��آ�X��,���xi�"����%T�J��=�o�����z|��7�*��UD�K���k>�-穝�9m�ԼT|6�l(-�v��v� 8�v�n�rWs��Xn�8�?��\v��1��)��ɨ���κ7��%���;Ƿ��w~|��Հ�q(t�%��B�Lѥ`|�Z��Y�Kb�u����t�?u���΍5\w���u
~:]{�����Fۛ�?�7�$~�p+��V���[Q��q+����ws��c�1P7��"�[1�<k ;ŗD��Ѹ�����?4&��#�~�j��������/V������7�D�'��������u���o���:P�����Y����-�ݏ��Y�Rsό��3��s���㖮���x������VFE[y���<���n��t��</q+G�����xJ��V��rOGW�?G�A����v��Ε���P���~�IP�-#��o�/�[ɏ	����ʕ�Е{�h[�����U�,�b�����уq�c����ӳ�bJ_�%�̥��J�a%Q`b�U���ؿ�e��s�b���|"�����q�QX��ӖG�=[��{���:<���t���@A^ixwT�:>˾6������|�����èx�U���xj�g{W��v6��sϽ�������X��S��Z̾�Bk�b�Ң�"�7�Y�V�9������c?�ҏ��qW�ǺJn:�~���7x�>�������X�"��������c�y�>���ۼQ�ᶣm��0�� �7��{�T_Q�����55���e�a�47������P��t?������_v*�o��&mj;�,���>�giO�g�2��}y�A��l%��g�B��0]d_U��ɐt��g���r����Ȣ N��,���;�_��}����)�r�}�h�������9�ߟg����^|s^}?�Y�?������ɫ[��)[�@�پ�;�������C��?����;��~Y�{+������B7�w'˕�bP ���)�����˕�I.��-�9�~zz؝`�Q�P~�{���L�hO^��#�`�M��A59�[����d�c�7�Px�o�`j֪�dM����s�N.�q;���OpL���/���Omx.\��G�"+2�
����6���y��C;K�O\+��Yq����J��	�ޮ��,ӳ��0�ų�z$K����܂��ay�\=�1�
'8b�"~���ݘձ�|g=���ۨ7İ`�ڱ"�Sp��'cܶ�/�J��S$�x��+z��	�-�����q�
�����l���k��6���N��O��Q��/j�sӬx!���d�R��L�vj���ty�r��ܽ5�3������8���:��eҊ����������>���:
��C����:&�X�{b� �t�].W�%��l�7t�N��#����8�7���v��x�-p_�E��*������/Qŷ�S�
����Gv65� �#�Rg�n��Qb����p��/9x~�[��9܏oP��(_�7F`e�q;4�}�
j�P�?��j��b�Cґ.��k՜6|f�B����YE�Ӫ-ñ}R�Gڔ�e[��xhE��g!:?�/b�߻1���������w	�o�~Zz�hi�r�s���vc����Y��������N|ɕϓ2u�廉 3"��M���V$�<b�M'Eė�x	H5���=���n� �����h�/����^�`�G{�GO�j4�0�3���C^$�n��Ƿ�?�z���!���
x�z��V�{
܉����s�u��\��O�=�1N�M��(׆�T%&[��;�2�?!/��λЋ��׹�VѬ�4�8�
���:yQ��aBr�� ��h�������˰�|N�|^F���j��Y*LK���c�~����'���_)_���U-E�)
��������>��z���yK��˷�ŕ�Y�����G��D��?��c)'s%�8˓(�9q��J�{�U�g���7��DH������,Ǟ)�[Ksk=���^���$�!��;:�mt(.5kt|�1{ ��tg��޻��zr��Zɾ�Ӓ?UG�,�(*��gG�\F�<3n��>c��K�g4�,������L�0��.�m+Ϩ�ΐ/����I�Փ̧;����Ң�+���$Ql�Ƈ���B�0���FeM:�TB}�脅c��XQ����d����W͐�;:�\n	f���-�|Uru��K���s���ŃAĜ�d:�{��"-ݿ9J��W��J4�k��ɳ�}]L����ty֚)Qy֧*`��w��#wnay֭�H�5�:�g��J�ۮ�y�|�"y�H��d|��F^2�̆V����7��/�r���u�m�]��۴�oډ{�Q�<�<'9��u�נ�>Z)^�8��?��UB�H�8p�Z^�9�k)���1����.�|�J��P���㨭��7���5sԸ�(c6Xf��'x.�ؚ��+����L@B���dr.�b�}(���ͤlد���BiC�򒳊���r7��p�Ւ"6�+����U�"������5RE��w�Yq���i��A��r���-Fd܃ΐ�Z<��r-�@�
=�`�aq��y4Xsw�q�#��\��N4SRN�d��\������#y��zb��1�_���5��x���*	��v�EZ?I$�cb�� �ͱg3�x���]E���>Ԣ@�Z�=�`��o(����8�w\�4^��z�Ȃ�q�_2Qz������BC�7q��T %�0LЧ�S3�mڳiצ��Y�7�������1qd��N�b�{\4l�/��t4pL��[|�I��$Q��#,B�
���G�	��W�kw�NN����M{�����!��<9�8?�/�}���D9�a�"�F��;ئ>��8�b=�$r��,�QD����c��<ϫN�V�Bū��zB��<�Z(Lr-,,���,�s��#{bz������"]�=����@���>�?_�σ�鑗��Z�xkQ�L�x������
�؛�?[�d�!�'�E���	�PP�<vA���G���@3pQ����(��ȳ7i��@��]������O�	=iK�o�3:���N���t�&-�a`}2�]%=����C��aʊ���Y�bēI�Kws?��M�����$D�Y�\)P|YQ%�';Yk���&��zJ0�7�a{�1�Ȃ��͘%!��q@}��RZC�u�/8���uܝ�-{�P����n\�s��I{COQA�, ��0�����^;	3�v�\�+����,�7+�/�����r�`)�u�Go��g
�#�񸔶����w��,���M���|+}op�X�Ge�?��`�4����#���I���إ-a�T���Z~�z�
���{���XL����Q�� ƨ࠿���^����Q�8�g�� u��8�0�+&c�����3u�
=~eԳ�_L�R�Q�T��ݰ4���>[�F[��>E|1���H���P��3ś��pi6�Aئ��
��/\�~S�|���ϴZPyJ��͉k����׽�d�Gl�ۭ�wOީJ`��$&���!�n��Hd����$��������}Z�:&�����	�S��O+y0z�� ��
�N |.����ڭ��� b���W]4������h"9����>8�XQ���Ҫ������|�u��q���9���꒣f<�+�m�P��V3���c1��]Q��d"~��d�;���ro/��݆�]�����ۈQ_n�CӢ�<��ͣ�+�����Γ���#{����d�̼��d*�#G�{JAC��(*�s7�-�e��1x|�:N[Q��)mP���G�!#=�w^~t�(IC���E�0�����<c�|_��X��aQl��h\D5h'n!�����8!#��M�ބ�?b��2t�����	�lt'߈z����U��w�Uڜ�d��m���
����	�E�[�W��/���3P���
�U�Ҡ^�� Vb���l�Zp+��;���X��#��Ꟁ�k�H�?a
���0M�W���9�4�#��t'"�) p���%3�z�G��Q�]i=P�Լc}���+3�R߭�c�u{�������'V
n.���3ϕ)):m��O�v�� �(N����i n�Kw�w�����C6�u4b�9|=�T�6�
`C��"�꣙r���
��}gO�˓��b}y�@2v���ys��}@�1%P�ԗkS~Ƕ
m�ߔw�� l.l�Fl��k�W�g'!��������)6�RGf)��Nӝ�3�� �w�E�->��m�!�n��;�Nid69C�\����N`�pP�N���Gi��vL����'�t��=��~"�$_��<\���c�#_iLʝ�e)�҄��J{��<�����V�&� vx;��6!�H�$�%c��)(P�a*w��)
�ƛh����8j�]���7e�&A�F�������UD�3��Y��e��ȗ,o�ʛ�0����yْ��"X��Kؓ,.?�/�l5_��yu|��矋Zܝ`k�YE8m�%q������K�l��~m,7���#���U�8N�E�8���4A��ƐV϶L ߯b����,M������{y��`����\6.:����Qr`�}��9u�)�Y?�X)
�.C�eh�+/���hh$|�蘼�w���\�albݤ�r�u���?E6C��
�bv���]ϱ�k����t��8�3|V��G��,L%j�͗
�f���Mb<���5��S�eEKit�X�����

a�oX�&+�,�6��>���Df�,��u<���&�A��9f�!x�j1Ӭ�3��c�1��l��p��h	
3�3�LI��������"��uZ�vWuZ��5�_�@������π����g�_X��ll
�z�Zh����3j�M�X%
���q/�M�.'�Q��혝n��A^T����m0��m�X�,r�0�>G ��*�m�|R�^e��]l�\;���v�g(�Zy���W"��.�����;4弼.�7�����M�и<��n�Ȋ�C#�6�_r1|����I-2�u��ZQl�� �����eY����a��k�&% Ѿ�*i�8~rFw%4N�BWh9��I�F�_���)��%ҭ��X�W=�X� �u^�ի���8���m����7���

// Skips to the first non-space char after the first comma in 'str';
// returns NULL if no comma is found in 'str'.
inline const char* SkipComma(const char* str) {
  const char* comma = strchr(str, ',');
  if (comma == NULL) {
    return NULL;
  }
  while (isspace(*(++comma))) {}
  return comma;
}

// Returns the prefix of 'str' before the first comma in it; returns
// the entire string if it contains no comma.
inline String GetPrefixUntilComma(const char* str) {
  const char* comma = strchr(str, ',');
  return comma == NULL ? String(str) : String(str, comma - str);
}

// TypeParameterizedTest<Fixture, TestSel, Types>::Register()
// registers a list of type-parameterized tests with Google Test.  The
// return value is insignificant - we just need to return something
// such that we can call this function in a namespace scope.
//
// Implementation note: The GTEST_TEMPLATE_ macro declares a template
// template parameter.  It's defined in gtest-type-util.h.
template <GTEST_TEMPLATE_ Fixture, class TestSel, typename Types>
class TypeParameterizedTest {
 public:
  // 'index' is the index of the test in the type list 'Types'
  // specified in INSTANTIATE_TYPED_TEST_CASE_P(Prefix, TestCase,
  // Types).  Valid values for 'index' are [0, N - 1] where N is the
  // length of Types.
  static bool Register(const char* prefix, const char* case_name,
                       const char* test_names, int index) {
    typedef typename Types::Head Type;
    typedef Fixture<Type> FixtureClass;
    typedef typename GTEST_BIND_(TestSel, Type) TestClass;

    // First, registers the first type-parameterized test in the type
    // list.
    MakeAndRegisterTestInfo(
        String::Format("%s%s%s/%d", prefix, prefix[0] == '\0' ? "" : "/",
                       case_name, index).c_str(),
        GetPrefixUntilComma(test_names).c_str(),
        String::Format("TypeParam = %s", GetTypeName<Type>().c_str()).c_str(),
        "",
        GetTypeId<FixtureClass>(),
        TestClass::SetUpTestCase,
        TestClass::TearDownTestCase,
        new TestFactoryImpl<TestClass>);

    // Next, recurses (at compile time) with the tail of the type list.
    return TypeParameterizedTest<Fixture, TestSel, typename Types::Tail>
        ::Register(prefix, case_name, test_names, index + 1);
  }
};

// The base case for the compile time recursion.
template <GTEST_TEMPLATE_ Fixture, class TestSel>
class TypeParameterizedTest<Fixture, TestSel, Types0> {
 public:
  static bool Register(const char* /*prefix*/, const char* /*case_name*/,
                       const char* /*test_names*/, int /*index*/) {
    return true;
  }
};

// TypeParameterizedTestCase<Fixture, Tests, Types>::Register()
// registers *all combinations* of 'Tests' and 'Types' with Google
// Test.  The return value is insignificant - we just need to return
// something such that we can call this function in a namespace scope.
template <GTEST_TEMPLATE_ Fixture, typename Tests, typename Types>
class TypeParameterizedTestCase {
 public:
  static bool Register(const char* prefix, const char* case_name,
                       const char* test_names) {
    typedef typename Tests::Head Head;

    // First, register the first test in 'Test' for each type in 'Types'.
    TypeParameterizedTest<Fixture, Head, Types>::Register(
        prefix, case_name, test_names, 0);

    // Next, recurses (at compile time) with the tail of the test list.
    return TypeParameterizedTestCase<Fixture, typename Tests::Tail, Types>
        ::Register(prefix, case_name, SkipComma(test_names));
  }
};

// The base case for the compile time recursion.
template <GTEST_TEMPLATE_ Fixture, typename Types>
class TypeParameterizedTestCase<Fixture, Templates0, Types> {
 public:
  static bool Register(const char* /*prefix*/, const char* /*case_name*/,
                       const char* /*test_names*/) {
    return true;
  }
};

#endif  // GTEST_HAS_TYPED_TEST || GTEST_HAS_TYPED_TEST_P

// Returns the current OS stack trace as a String.
//
// The maximum number of stack frames to be included is specified by
// the gtest_stack_trace_depth flag.  The skip_count parameter
// specifies the number of top frames to be skipped, which doesn't
// count against the number of frames to be included.
//
// For example, if Foo() calls Bar(), which in turn calls
// GetCurrentOsStackTraceExceptTop(..., 1), Foo() will be included in
// the trace but Bar() and GetCurrentOsStackTraceExceptTop() won't.
GTEST_API_ String GetCurrentOsStackTraceExceptTop(UnitTest* unit_test,
                                                  int skip_count);

// Helpers for suppressing warnings on unreachable code or constant
// condition.

// Always returns true.
GTEST_API_ bool AlwaysTrue();

// Always returns false.
inline bool AlwaysFalse() { return !AlwaysTrue(); }

// A simple Linear Congruential Generator for generating random
// numbers with a uniform distribution.  Unlike rand() and srand(), it
// doesn't use global state (and therefore can't interfere with user
// code).  Unlike rand_r(), it's portable.  An LCG isn't very random,
// but it's good enough for our purposes.
class GTEST_API_ Random {
 public:
  static const UInt32 kMaxRange = 1u << 31;

  explicit Random(UInt32 seed) : state_(seed) {}

  void Reseed(UInt32 seed) { state_ = seed; }

  // Generates a random number from [0, range).  Crashes if 'range' is
  // 0 or greater than kMaxRange.
  UInt32 Generate(UInt32 range);

 private:
  UInt32 state_;
  GTEST_DISALLOW_COPY_AND_ASSIGN_(Random);
};

}  // namespace internal
}  // namespace testing

#define GTEST_MESSAGE_(message, result_type) \
  ::testing::internal::AssertHelper(result_type, __FILE__, __LINE__, message) \
    = ::testing::Message()

#define GTEST_FATAL_FAILURE_(message) \
  return GTEST_MESSAGE_(message, ::testing::TestPartResult::kFatalFailure)

#define GTEST_NONFATAL_FAILURE_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kNonFatalFailure)

#define GTEST_SUCCESS_(message) \
  GTEST_MESSAGE_(message, ::testing::TestPartResult::kSuccess)

// Suppresses MSVC warnings 4072 (unreachable code) for the code following
// statement if it returns or throws (or doesn't return or throw in some
// situations).
#define GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement) \
  if (::testing::internal::AlwaysTrue()) { statement; }

#define GTEST_TEST_THROW_(statement, expected_exception, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    bool gtest_caught_expected = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (expected_exception const&) { \
      gtest_caught_expected = true; \
    } \
    catch (...) { \
      gtest_msg = "Expected: " #statement " throws an exception of type " \
                  #expected_exception ".\n  Actual: it throws a different " \
                  "type."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
    if (!gtest_caught_expected) { \
      gtest_msg = "Expected: " #statement " throws an exception of type " \
                  #expected_exception ".\n  Actual: it throws nothing."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__): \
      fail(gtest_msg)

#define GTEST_TEST_NO_THROW_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (...) { \
      gtest_msg = "Expected: " #statement " doesn't throw an exception.\n" \
                  "  Actual: it throws."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testnothrow_, __LINE__): \
      fail(gtest_msg)

#define GTEST_TEST_ANY_THROW_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    bool gtest_caught_any = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (...) { \
      gtest_caught_any = true; \
    } \
    if (!gtest_caught_any) { \
      gtest_msg = "Expected: " #statement " throws an exception.\n" \
                  "  Actual: it doesn't."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testanythrow_, __LINE__): \
      fail(gtest_msg)


// Implements Boolean test assertions such as EXPECT_TRUE. expression can be
// either a boolean expression or an AssertionResult. text is a textual
// represenation of expression as it was passed into the EXPECT_TRUE.
#define GTEST_TEST_BOOLEAN_(expression, text, actual, expected, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar_ = \
      ::testing::AssertionResult(expression)) \
    ; \
  else \
    fail(::testing::internal::GetBoolAssertionFailureMessage(\
        gtest_ar_, text, #actual, #expected).c_str())

#define GTEST_TEST_NO_FATAL_FAILURE_(statement, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const char* gtest_msg = "") { \
    ::testing::internal::HasNewFatalFailureHelper gtest_fatal_failure_checker; \
    GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    if (gtest_fatal_failure_checker.has_new_fatal_failure()) { \
      gtest_msg = "Expected: " #statement " doesn't generate new fatal " \
                  "failures in the current thread.\n" \
                  "  Actual: it does."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testnofatal_, __LINE__): \
      fail(gtest_msg)

// Expands to the name of the class that implements the given test.
#define GTEST_TEST_CLASS_NAME_(test_case_name, test_name) \
  test_case_name##_##test_name##_Test

// Helper macro for defining tests.
#define GTEST_TEST_(test_case_name, test_name, parent_class, parent_id)\
class GTEST_TEST_CLASS_NAME_(test_case_name, test_name) : public parent_class {\
 public:\
  GTEST_TEST_CLASS_NAME_(test_case_name, test_name)() {}\
 private:\
  virtual void TestBody();\
  static ::testing::TestInfo* const test_info_;\
  GTEST_DISALLOW_COPY_AND_ASSIGN_(\
      GTEST_TEST_CLASS_NAME_(test_case_name, test_name));\
};\
\
::testing::TestInfo* const GTEST_TEST_CLASS_NAME_(test_case_name, test_name)\
  ::test_info_ =\
    ::testing::internal::MakeAndRegisterTestInfo(\
        #test_case_name, #test_name, "", "", \
        (parent_id), \
        parent_class::SetUpTestCase, \
        parent_class::TearDownTestCase, \
        new ::testing::internal::TestFactoryImpl<\
            GTEST_TEST_CLASS_NAME_(test_case_name, test_name)>);\
void GTEST_TEST_CLASS_NAME_(test_case_name, test_name)::TestBody()

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_
// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the public API for death tests.  It is
// #included by gtest.h so a user doesn't need to include this
// directly.

#ifndef GTEST_INCLUDE_GTEST_GTEST_DEATH_TEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_DEATH_TEST_H_

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines internal utilities needed for implementing
// death tests.  They are subject to change without notice.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATH_TEST_INTERNAL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_DEATH_TEST_INTERNAL_H_


namespace testing {
namespace internal {

GTEST_DECLARE_string_(internal_run_death_test);

// Names of the flags (needed for parsing Google Test flags).
const char kDeathTestStyleFlag[] = "death_test_style";
const char kDeathTestUseFork[] = "death_test_use_fork";
const char kInternalRunDeathTestFlag[] = "internal_run_death_test";

#if GTEST_HAS_DEATH_TEST

// DeathTest is a class that hides much of the complexity of the
// GTEST_DEATH_TEST_ macro.  It is abstract; its static Create method
// returns a concrete class that depends on the prevailing death test
// style, as defined by the --gtest_death_test_style and/or
// --gtest_internal_run_death_test flags.

// In describing the results of death tests, these terms are used with
// the corresponding definitions:
//
// exit status:  The integer exit information in the format specified
//               by wait(2)
// exit code:    The integer code passed to exit(3), _exit(2), or
//               returned from main()
class GTEST_API_ DeathTest {
 public:
  // Create returns false if there was an error determining the
  // appropriate action to take for the current death test; for example,
  // if the gtest_death_test_style flag is set to an invalid value.
  // The LastMessage method will return a more detailed message in that
  // case.  Otherwise, the DeathTest pointer pointed to by the "test"
  // argument is set.  If the death test should be skipped, the pointer
  // is set to NULL; otherwise, it is set to the address of a new concrete
  // DeathTest object that controls the execution of the current test.
  static bool Create(const char* statement, const RE* regex,
         14��l����@Q����ˌ��=^\�я���H48è
xެ���Pa:���b�¤^�jk�-y��}b<�
�;|]_������c��ż�R+����PG�c1!����|�4 �����dr$�T	�N�z	Z*G����
�O�4Ѱ<�k-u�}`�\��3�X?G�P\�*\�';�a%��U����1#��ʔѨ��$.�c
^#t��~��j5���"�1%r��Df�+7_0{�������<��.�|E����\6-���z{H2�{(�頤�i�\j����L�%�6B\�6�aZ��.q�f
����l�k�S[T�Vd@&!�c�o�ѶW�s�~{�f)��;�?$���"s�h{6 ��r3�A	���۱ ��얯v�C�%��T�"�N`fE8	����&X�lGK���nu�$�C��|���a�T��eny&Ȉ��ti+�L���%�M
e<#{�֬N1��|d⌇��6�����D�`�t@|��ULV��.�y(�ʻ� ;!ɘ���A��g�z�1P�]���%h�,��$��G�g+6#Za=�\���V�9��ۛM�Q#0�v�豇���,�#��	�k�Y��	!��@h�)8K��i'�V��̫c5�*��1�/���e5���}��9��A��&qu�$�����T���}F���lJ�O�xFo�^��60~=�����/h/4��5ت��Arj��r�(�B"J���R)<.B��m\Q�\�:���.�T7�����^��P2��&s�#b����r����M�Q�W{�w�$w�䁀�^D�����ޥ<;����a�����+6�S}Lǔ�����n֥+��py�c
35⒍F�t�[�<%i�Lu
Ga����F�b����i�E�j�j\�H��e� ��{����(001��|T��ż=SmG�|)4լL�.xhWjC# 䢞qɪ�k�R'"
�,�
��6�������U�q�>A�W���?( ��<-L�ט����A�[}���	����HC�uʜzr�А�a����`5X��*5�������n^�=���W�)�|��P�/�@LL"��|w"u e��5�N�%���E�E�A���5��)����װa�����f���m���9��lk�2�Fd�_Xim��i�ɂ��{
�s�8��Vt�E��o�!�*6u.�2��$��[��g�R��b>C���.�=�����W����؈�u�J�n�
��WG8�CS��| ��A��*͏H����?j�E�d �XL�q�UR �ӫ�ߵ}�]�x�	�Պp_�Z�F#r�?(K��?�'����+N�ܨ�ou�d��b�r�߸�:�B�t=�҇;���ր(Ik�CMV7q�ڋ�Lp�UT��s6פ�8�@λ����V���%yș�g�f&�p�^����eH�]���'t�G���.��$	��.hJj��K�s2�|�A�<Q#�Bu�؝B6��5�/H�@s1��8�W��}�H�D���r�F�:Q�,^��j��"�q�PᨪB��lf[�=��P�\�"W9^�1�b���0��|��q��f-씖7���x��4ཨ���z�:�aŃ}�0@Yh�r
��"��ȁ������]�|r�X�h]�[�l��)-�hd�ǈ߀��^�)��	G6�zK@���]�����p�g�9wL�	�#.�8��Q�s�7
�L����c�ǀ�P�EA3�7"(�[T=sVcx`8OP
9a�"�Y�{�ŌĢ5S�RҖ�ʿ�4��e��B���.�'bt�[�x�a����mon�imh����B=�`hdtv*�*4Dp�	Һޗ!��;�
��w��$�Ⱥd�j_��d� �k%��(Z�E�y^�!�9]"�>������y?�W�WE��Xv�!W���AM�F�z�$���
<Y]<at��&���������$�Ө��N Y9�I$j�];�2޾?o� �O���������/��h�v��Plz�W(�wy���
���Sb5q5������V
�{M��<�:����8��8<�P�P�"dE��`#;S1
�?H�I�e��SR�wHHV��"�5Эi��Я������������=����_���R�n����������%��_������?c�~�_�G4�[R\�-|����zY�Pq�h�����u�ߕ�P�[�
��
_�����n9
��C�Mn�+1��Nv�i��0
ԙ$t8F��|�͒Qz�$ �����u�#�w��5���I	���Qr��;C����|6��,)o\��((�И��C}z���=�\d�l\�s�	�o�<s�_ )$��p��vxB}x��`���c���v�c0�p��(�X��U�	���!4z�&I�$	u���sT]��6ν�i
�ny�T�<�@H�g�T�eU�f4���o �v�!���vVZ@>�<�\�8�k���$�-�8��r��~�
��)*��t�臢A��m*;Г�0�׸{��T(��� ��g�cT7��s���p�]B��-ra0�������[�V�]n�61`#�����0ܨv�O�,X�e\Y���:ףG��9���0� �t�]bSM���Y�YW<ąG`$)9���d-��{�(M}�3��ݾM��8�Ԗ���/O�<Ԕ����B�X�t�P�����Z�����8�3��xx�'>�n��1˶#��؇�J:�Yv�Ì=%���%�(s���wQ��G�	ۄ���0,	~�����8�4��.����a�8�ڿ��eg��Q�^���bp0��:�%�
��:�Q��o��\,��� ��7LJ�ӕ�ˌ�Eb	��eV�jv:��^B�C����H y�A�����V�$���H�o$q>�e
�w�Y
eۛ�� G������L�����ݟ_�Gs$��r$�@|��o �/�����fD��;�cD��Q��5*'�.��F�����3��������Xj��J��̇��4����Д��$X��8�Oj�M�{=6��o�_E�����O�� E'�� � �t��4�����G$�N���;`��ħ��n yS��w�������B�#��5�9�����R�!94��@睤��'�be��Ȫ��G��%�V�f�ޫ��\�r�o�hh��ĕ�w�D���؈:`���E�j�0Y���K}r�F!.Y���1n�><|�c\���zS/I.18eA���ot�Lq��%�ub���p|b �*\�:'��K���F�F�3 K#���r��r�H;�!��#�PA	���0�r���r�0�.� ����f'$#���*�`�[��5�
�$m�
ˢp��;j���$��(熜@�����dy+zO�y�%~�}WOr�6����}��7X

�����z��Y~A9	h�*�-��7x���9��5�[`-
��Tރ���u��#�����ެ���m�?~�L�踟�p����7љ�<���&�|Kx�E���1�z���	��+[p�34O1:�k�� �S�]��ؒ�\c����qن�h����N��፶U����d�_O�GK�
�,2<��]�9�]����^�$�4k��81�u��%y��ew���'��Bp|�»&j�K�2�6"���I�eA�U��%�51!�|#��ǈxf����cQU��ޛ�i�9�JM+���_q<��A�Z�����o!��Lڄ_��Z��Y��%Y��Z�ğuz^��� ���GɊR=h���-ߟ���&�U�b�ι�������yK~�&�X�!�f��(+" ��12u���V�S�&c�>^�̢q7��ya�̀�-�}^�����˃���Hm�2�������2`m=azyP) yX�0���{oi#��*bx�p<���m����8�E��w�
�Y��9����mW�4��2:	۠:��ˢ�.���g�+������6���s.�&]�]0|��� �E��5N�?����<t|���YW�J��[e�t�6��]/A<�p�_�x�Q�v�f	��֨�mI8o!y���TK�$�h=r��;��*[�<t�����~�<�2��)G�Ѳ{Q*^��n�N��n!����³h��B܍K�;|߅��]�f�%	�͛��\�����x/�n�U�0��fd,e4G����
��	�J�CxBU�
Y<���Ӎ�t����0�qG5(�Z����s����4��e�8G��nk����N:�˄@�LWz�#e�/Z�>&84����M�a�qR�K8�B���������o)��-�D�U<���VnV��J�p(b�Ny�˄��r�(�MUc��=���"�/ �ς�76��×yyw^�/嫱��"���U����P�!�X��P�s(_?ZB|���)�!�	ָ���`�����l��Ԑ£���q)�&yħ�<:��f;���ӈ���Z7q��x+���O�f�o����~�H{����;����������xX�����_�s��1�l���M�u�%M�#��80��5:0��n��������C�����ry6z�"�l�M��M����6XI@<]`�VG� 3��3 i�7|��yTB��X�o��ys��ܥ5w��-��(�w�=���%��Ǟ�'&�	T�����3
�*����qr��C`d�����i kbe+d��sp`��AA���}�9a4EsP�������"���WY�$�Q�C+A���	���Uc8��j�!v^IB�D`�E��~�A�|��-��������!�Qe��8)��#��B�Ж�X���1�3�w�ǥ���\BW@a�k���R7��Rmq��ّ���JB࿮���'w+a?M��~���S�KD�R��1�[;V��F��h潊fb��� ���s<I���	�d�S���~
#��-�oxV�6�OD��#��Ք����O���l���n����s�\r�|TWB�	��#��
\Z��B�;�,>�at�Һb�Xf$�4z��cN�,�6&?����X����*����?Դ.���D����ߋ��s3�ZK�^��(-SV����L�����[�'�����rq��e�� [� ����D+0�4��� ��P��4�pz��c��iU����S�/��:p�^ }�A���w�����=lm��U�����n�T�+~N��;V.c��W�/�,��;�O�/6�eu��)��6�jV6�t<�d�X����PsA��9���ǅ�]���
�қ�g
t��s�)�}�]�� A�Q6�ю�	/��!=#�i�;��%:A���>L��a#��5��i6:As���s�g�9'Ƅ�
���7������7�~(����\�������Î*�a���e�V���}Y�ι��C�m�G\gJ��<�)@w���9x�������
t��#���u�1�
(l)~[�&����
�M mU��P��z��q�q����y#7�2pAR|�[��k!��M���#��
_�R08X�&cO "N����)��8����2�Bx �O��a>py���u)�3~jD�F>�缾6�����y����M {,?��O�*
/�d+�9������1ng����p������sf��+�%z������E��$�a��dI���ߗk�A��J%�~8�wI8���&l�8��X����`ج�kTI�q�8�_���q��-Y�K�!��E��݋�����A�s�;M�����ў�,���C��1�����=HM��[�'`��3[�ښ�j��i׃
u[P��D�z�&�LAo,TWgEZ��?�;Q��pc'j�N�Q�� ���
�ƫI5��� ���)^C}\}^<��Okd�EPI@�������9�h�_���$#�7uGK�c�j�n~�̭�V�?2�/6/�}
2h�,�Lo��r��{
�a�E+�5��X��+'�ygU̠r6�����X���I|`v8�%S	S�ptn8�A�?jP�r��=(<f-~����c	�����|=�C~�!tY�,n���͒�ʎ�{���acul�Y��g���Փb�M�1��'
ʊ���ơ|��:
}��Ϩ���w��+�(�<@W�v�Q(ĭ�<�(��-�J~�9HKJ��4ʁ�0��r9<�se�p�^^�w�M-Qz6��V[���xǿ��E���'Mv�� ���  ׉Rʾ�L:��������5�k�5"�pq<F,/�x��uI�=�?�J����b�:�5���\��U��3����&Q�<9v�w�*�v)�'
{a���v�B%��W�XT~��q1�VR8���G�}<W^������+�i�������c�넋R�G��▗;K�B7��[a(�e)�΂�,��J��3>�����8<h!p*��g�~��T�4~?�̐��Pu�v?t������5m�����̗��8�� ��d�Z�g��֐���t�6a7�i�������@�7$�X��m����^ʆ���o���h�9�юߧ��|z�?�?v����/h�4��.�;��:�:ꄏ:
������ш��s6y@�t���@�"g�}� �O9E�`��x�_G}3�
~��n-��Q�"������F��7�!33s�����JG(�0~:���N�����$���Q����uN������[u4�|hK�}�>
ݣ1��/���)m����!aT꿰=^�D�*=�)��f
g���/P�-
O]�)�ő5P-�J�IU���9�-	RB��DV::�O�3�'h����m3(6�Yyj����1Lhd&t�C� S� �e�û�Molx|
9X�����ǻ���g�&�Ք��`XtN�������~�i�h�y� aj��z��2��-���sb%ʣ
3�h#��t�ţH�����,��
����ih�O�qFfm_���.��"��=�E����Aq6�����2�o���N�i�'�sm,o}��t&Ĺ�.5��L��̈́�xނ���Z>.q<�W��{BS�E���f���.v���=<y���Wn�m��ʹ|�E*��\���1�N��D9�ɳ�c�s��J���I=����A�G�y:�|ev�;�í>ƚ�zfX�ͤ�A��5�RR��C�>x��M�N�g�粽����g�1�2�ùF�w�>;
���$��@*J�㉑�ԇ�ϐ��#==1
���.��Cj���9�2��DH���t��Q�ʤnkG��늈���ѕz.�~q�=�+�����)d��
en0��)<�����#���˿��c�ґ���� t�܆���7�x�����-�7�|��yp�<�,�0q�2�h��-� �<��O�4O���tIyݳ���P�*�<�┋�y[���9��7�������A9���r� ʅym�R�t��� u�����?����9�[:�����%4 ٠�v餍��M@w�Y/zi����':���U�fT�QL�Uz�}�]��ǌ�1���xT��"���R4V6��MĠQ]�J�f���/��������'���N�Ğ?!�0�W~�?԰~�����n����h�Dl��8�����.���,
����N�����^�XA��;�#�Cl�E'���QKZ�r�7�G�k���S�9�jZ|��Ljo#>4	�V�r�~��⢝�ߞ�?�GPv����?��&�)]`����wj"NN,�~����42��v	=��0��<�]fr�ѐ�Gh��<c�*��h^�<j�E��M�ٖ��v���� ��횳��u6,�,W�#��|N��p���s�9�������
:�����P�����Vt�t�
l�<N�d�Kh��yJ��F8eB��]ʄ��
O��y�ۜӔ`��Su�r�O*�IŨ�x��*[�d�:>GfF�0�l=����(�����M��bm*�O6:�tC:�䳔�E���B\VŚ�sc�ېK�,��]���6���$�̡|d���Bt��u�9ܵ��F��irԥ��@3��{�сϋn���I�^����ǰ|��rVN�t�G��s[�{�>��:��E�faL�xUl����E:�����E�"�H��Q��L$�P��賬�E�q�]������o�P0ϰ����e�c�{O	;Xb�a2�t�x9ހ��`�mF���/��6�m<����������&���I�`?����^�o� ���M%?�y���#�s=�����/���k$�#*I�7��� �ꬷ����J#����������O���Y��٬�4�;����:�����y�ױ�����K;������}#�3�H. #�qg{)��)��V��{bo��-���p��_�?��&��F�B�US��9��#�}�m^:"�zP���~<i��6�C�BY&���Wq�};lk�V�4��D�����3�{�_ˣe*\0 �y"q��=�6CwI���P����� ���YC�	�K��5��<��'����k������b�݃.���'��$���ϜS)���|�wN_gx���<?��U�z/�z/b�G/���Yo7F�ܿC�).}�):xr�<�"05Lp����_Ho��F__yh�⍰�z�l��[xhR9w
s!v�n���G	�����5zf�#o�,J�a���;�9}�t
��"�oߕ��V��gx��X�0V.��{����0�
�)]9Hc��^ǌ4$�f���.�po�pG!�n�����w�������_>�������^�
6����`nqޠPƄ�u�ײ��Q���
^w7P��;�_w7��pQ�4N|s}Z�r������x����]�(����lG ٟQ��s������|��7�=���w��1��$�cF<4[���h�[�~	;!1U�W�_Con��F2z��J�������:���	ͰV;�Kϔͱ��������nB�f¶_���`�
`���9��]]��B�0��r
��v�X������K�zl�ì}��0�c&��Nb��H�Ȝ����C��j��ȕ���K@�뒯vwͽ�^t���'X�x�i��v,�91q��Z�v�c|6�~���0ſ�M�h�����_��߸��b�2L�'��
F}����C�_��C��V{�#'�.Q ��UƇ�'�b�U�|DZ"X����ıy3e��d�G�z7����DXW�E/�<��W�*ɇ,�F:diN6�tK��盡��h���^aVν�Ƣ)�ݿ[�E�b@��}[��z5u��d�C��.��X~����CvY��R~nY�,�5��v&�3���y�i$�X�[�8M�Hl���@��x�:	X�;ӢQuq�������lh�b!�1@Tc�y��QFj۠�~5B����}��[��x�R,%�7��~����A���9��������I�[�]"�*GTJ��(p2~����N�EN2-R�H�^-+����]��V:�`q�ڀk^��]N��5�Cϭu����
�um¨	�[E�*
�f�2�hv�6����G���}��!iG��X��l8���vP�U�1��ِ�+#T%sB{�B�pA�������7����; <�V}-��	n��m[H��=�S�+Ԫ�QFx�?1H"Z8ы_��.���=U_��I|�����N ��q�@����,�=���!g_|��f��aZ�F�b�4ܑ�/T�E{�	�K���제��JI�t:ȯ�]Eo�3��H�9��S�S7�� �fЉϠȎ��T#f_~�tk6-���Hw 2���l9L@��P������>�A(�d�`s��������)U,r�[��Dٶ|%���'@�����<
�:�+��x�'�,ܷ�?8�^Q��;�l��67�J���w��ē}8�vmR�Tu8.à¤��t^�فKय��v�cy�$�,>D89t��B�&�8Ô�I������������_Z�n�_�O_���}����^�c�\Y�����y�����߁��`�TP��p:)?[R�H�� ��e��uZ�����Մ�x6w�γ��x��Hw̳ꑳ��Ĩ"N@YبD~�vf뮡8����3-��Q���G(��^�e_m?'�7�/�o�G�?L�5�gh� ���t���0i��-�y�A���Y�B�y-�� �s���Gb�q���'>�
f~��;c�rz�f�E��oT^��cNJ̿�o���O������?z���9J[K�`�ި�9$q�V�����Ey�iw�A>�S��Y�y��v�����z��g(S�Lt�.��[�Y42=���G,nV*�xB���p��f��n���i���]�ט��,r[�x3��w�}���;r�;$�=!�Yn��b|{<��|�~��w)&�ӳO��{���_��4�*��
,p��U�_m��SX��>k<^�!����7��>��>�{M��'-\�5��Ȍ[�<2�;�k�^��^NK��Y�N_���Ɲ�ʩ[c��ʤ����8�M����/k�������&�g̝Cn
|��e����VW�qZ��� ��] ʀ��c�Jsb����\
M�`W{��F���5\��[\����`((�v�
�ʧP>�����Ϙٹ�ӻ���a�6�̵^����E���r�>�Zi-�{:�t�I�Yy?/^p��(~���O�����r*�w;6QJ=ov�\�,w�7%�Gk��>Cx�DM�lR,�(i��.yX?�;4�^�re\?fÌ�$�#�|?6���ԝ���`Bς���@��)��"Qe�-B<w)��&J�;1�}';���У��׆Ã���5���H?��x��2	@�7Ec���N�
��{D���ҹ��ÿI���eK1`�ӣ�k��	z�N\O�fI��
�~`��~#�����n2��;�*m>ߺ��BBm���m����F�%�cݣL�!Zj�m��1,f^�]�e_܀y��3����V��`"�+�-c���l����(Ǘ�z�5�޽��bH8��ڤ��o$��1@�_1�|��J�⎉�Z:�&������ (uRD{��%������}�,w��kHZM�|`��;(������L}���ާAeuНR
��ת���(��
�8������L����Ӌ�4E|�����b�������<�P��'ڣ*Ĵ��7���@�2S����ډ�-�λ�=^�`J�}`���7��ѻŴ�����swT��$ٌy��A��~�{$��1�Ϳw�_q\1�2[��s���Lz�2_u�R
�%H�Y�Oĳ6ȼ�ԅb�	Y	��ց���꿭��T��WF��8��uXm`���y��m�І#y��-�C���S:���֘�	r���G���� )�����<r�4G�ӅXz_H��!y�	_��@�ϒ�l��4�\wP< U��(��S7�[���ߧ�}}��3¥ib�4͓jzoW������KCN�e�Fq]�����t�_�YW�2
��|���.6�Kt�>����9cPly=��fN%�����$�V�g��`�3||
�F��_���[���4�ۡ������uF��P�Wl��h%ݳL|?X��@�ۻ����]����]4���z��nG�m'uҍ<3`�o/��E���;q*\9x�:�qC� A�����p��!��~t'�_�пM���X�;~������woU�<w�� Dv}�(�re&QaL �p��׺_f^2�9�0G��z��((�(*�}���!j0Q� ��n"qwE�����\ɄU�������~�WU��U=����_{:H��7����?����~�z�d�����t�;�V$�%���Z�c-�~OKb�*}��`�Q�C�я���EYsT��_� �l;�;��˳N)k~tGB�7x�y%̕Kn�F?��i�����M����e��nGj�ˇ�e�^��?�r ��$�6Qݗj��s+�\��,5<ϝ�qt4�6�6堟�>��_BW^��U���|�%K	���x��u���NH��;��Z������b-��	x:;�� �x��7a^�Fk=�������[f�B��>?Eu�������Z���zBG\X�2��a�f�{��Z�����%�����y��)��9`�퀬.>�"X<�r&�?��~��ޣ~�ws���27�喼�p:�w�H�vs�<5ߔ��g]�m�s;q�a]`>s]���K��}@�?c�\�F�oj�+|�k4,��~����?�������7�{o"d�2p]�re�M�sk�-�t�cJ��of�&j��#�۵2��ȕ$0)F]z#����i�)긻k�e�j��t�3���s��g��xWzp?�>��^L�q�vw��}ć�.k�v�yj��0�H1����o�1�_w�
��0���=1�v�v>�1�*b&��!�8�@���](��W ý
�ĔF��W#B��Ź���J^EK�'�������4Ǚ����`���u�ɣsu��E�z+��c��:R��t/�ۡ����NsY.���?���zU�G��<�9:7�0�8������ގk.#k'��ݽ�['(rjS�s��r�S��v%f��(���gg�(�4
h�&�=1ťI���鞠��6ʭRn�\�2.�;�ԓQǲ�i\
e�e��2��5>�=!^)�s�'�7�=hP5M,{)�+���p�~��͑yQK#W_#����F����#��|�l����V�~���r��~})	�}*��
W�� �����#9��ѡ��jU.�K:�E��{$_���D���	�x��l�u��|��O���L�a8��g9�������^�k:K�&^�k��gd��O��Zޖ|������ކ��8�Q�e������Q$�����2���^���N��>��6~<��O�xDYMﭫyO�d�]Su��&���-�/	)�Mr�|Z[��1�ǡ��963��5�Z�A�����+�Q-�Yo(+OѩF^��N�/�����]�s\��=-u-�|�ژ�����5l�S��qG�Z|�=��ͅ��=48�jy"������;7Gl͉���8Ƒ��u�~�;)�Ë��^�9��L�:�	�*4?��dٮ܋��q�RN�({�;�ٕW5Y���I�O:�ǝ�:����OH�������Z��LU�Tכ����B�"(��8��X���ׂ	�ӡ1f����M��Z���6ȃ��߲_�BK���o�|>��Me
�7cs]���~�onUk,��=(ە��?�l���������L�w��7�u� �W����v�{5ە�ɺ����?��?>	M�����
��z
���2�"GmjYk��U`��`�~�'�+b*]<�G�v�|�!俑��?]{�^�rx�5��N��Ǵ���*R�5�mи��Nբ��ڞ�'�n:����zR��~�/"�E�z��u;��rǀ�})汀Y3
��O��-7=�3{%#���!�n���
F�(����P�P�mW����zc�^K:���2�� �W)ӛ���:���z9!������}�1zM?0z���c�dzWzSz?&tF�LB�^CB�ޑ�^� ���`��dzNF��F�	F��Sz|��!����֥��@z��b�%}��%2z}dz}��N����->H�)���o��ַ��_F��?����c_�g�6�Sz��wFov=!��~z�{��#��������
����������)���}�w.N�w��W'�^.���;Fo/���q��[�(��q�ѫ���'���Л����^d����dz2z�vJ/1��O�Az������!==�%�;C�;��XF﫞������-�
��{~�?��t|��~��G�]��<��ɮq�]my�c�c2�����V��[���ۋR�\���f���_�����@�G��Ĳ�s݋%�
g����]�Pb/$�=�Ui�L辖������z{V��5w�\��ޭ3��W�<X��!>�u��Vz���17&�� ��s]m2����([kϐsE`M��޽��k>�|&�ҿ^PB;nR�����TK��&r���΁��8�램�q��w���޹Qw�nѥӝyrvǑ��?؀��!�U��t~�T�Y��9e5�:���ł^����hy��7v�V���Q�;Ж2��*��o��.�9�����zw���'�ޛ�ģ���~5��LU���^��2���d�tݟ�wkij���9	z��w�k����X��i���bo7PX�0/Rg�n����t4&t�"Z2$���[Y�|臣���H��"JY�:=�d��������&�KGR�[-�7��]zr�L����؉��x�7j~���ʃ��þKj�|�zaWf�@�NQ�V9DY=4	O���H��|��0���q��r2�j����e5Fu�B����IM��Y��/�z@
)5��&{W�뚦��(M��T����7�?��P�j���A�8Y��f��;�Ԧ�Qf��f��5�����q5����e뫩MT�ٵ�W�\��q
�?[A��庻��p
G����F諩��$r���	#�M���zv�1�e����Eq7J�gʀ垉4c�+�3q��)���A�z�R0(Q
\h�vCD9
v�g��a�=�
�ܽ��14.�����KG�����L��c���ǟd�]�H����Z�A^Ek�9M�a<p��A�����)�g��P���&�k-�*�w.M��C�ef���L���{n��8Y��[�[�Q d�J�#�8�����3&�.��Wڊ,W��下�֜����;������BT�����;.C�'�f�^x�h!���YW����A3@�������Z�z9piy.?0]�k}=���zGWy�Ae�pv}��;��G�G3 ���14_��Q�a��2�2EKO�B%=I���=.�ö�9e�3�u�L��1
�N�0�X$�M,4
6�l�Z�@0�qH�7�F�M��|6g=�	F�$�+����/r�ŢY F����ۭ�<�7��!u�-�!c؈�9�9�yA�0��aÇ���xôPo�PR,,�T0sJޝS�s�M���3��N���.��@{v�s��0�x��U���X��sG_�̜M/9�:Nϗ\� ��3
���0�+tعR��0��)�Z;���V��.�8�`���a���
��g���x͇~|o��r>W�ύ��A���o�y�����<��c�p^��W���C!���>|`Z�=Wo��k�{���o����i���[���B\*��wC³�_��ч=�p���f���4xR��'}>���P&�ˇ��oiC�ɇG�C��q����bH��t���A�|�|�ob����0��?���=-$�x�=e\8>|��7�'l�S~t؋���V`���#�F�/ͺo勭�E`�@<(!�uB�0�C���_��Dˏ?���8�i���txpe�<7��7w��B���F�8V��OWxbCh���܊��:�}_���܃�G�����[xn�o��s|x�?<�M}@��E��WtH]ۇ_�	�����ȏ?.�]ژ����xB��k���	-�u������^�c����$��S���������s��������_�>�����	���Կ��|��Y~F���K�'��).0�6{�l6
��\ڹqP�mc�:���D�l�lZ�h���LI�6�=v��$X��@�Y(-0�v�>,]F�/X�!��
v�`e��5��ST���ڟ���w�m(ȰQm��|T����]
��?Z�;A2�B²ۅ�F�ưV�b��
G�����Pl���Cy#R<.����W(�ġ�]$0�g��K��G�s�C��琑�3�N�B�����˝�8M�n@B����e���,���e8y}���_�m��	�E����LV_��$r��i�N|ߞ%7��O�!j�px�wU��� ��q����R��&)%E
�ڥ����}{l�����֣�6��Y�3��ʍ��G����Ѡw���I&���}{������^���;{��
�PΞ�n#�{�4�}=ﲸ���al���|��gyq9�S|�����t�����e�B��M�]{�9pC�W@�e�q=��f��TG��^m���^
O5�%B0uЛ�ίj�W��Le��A0#V���؟U�u!`F�
��!0�z���M�qP0P����{2�|�0�:���NG�	��Z8����½�pof�W��l�$�y�f�e�h6�� �
@� �I��'+m���B=�P�M�n�ƒI�by,��X�C�LR$Z�B��* eAUT�L2ш�I쉒U��Y9�z�ȓb^4�
%�D&�%��%,��[�ɠ���j�fR������*����X*��bltFP7���g���CU�f/�7c${�b���5����eS1\*�K%2\*�K�p�.åb�TK�f�����R�q���R3\j�K�p�.�0���d�2�L�+SN�pe2\�W&Õ�p�#���H�k$�5��)�d�F2\#����p�b�F1\��Q�(�k�����p�b�X�h�k4�5���p�f�F3\���r>�k4��<c�1��k�5���p�a��0\c����2\YWÕ�pe1\YWÕ�pe1\Y�M1w�L�3W�$VF��0�I���`��!��P{��+��F��(��^c؋�ɲ�.å�.åb�T���R1\*���W3\j�K�p��8�K�p�.5åf��K��pe2\�W&Õ)'a�2�L�+���d�X���H�k$�5���p��S2\#���H��E�b�F1\��Q�(�k�5J��p�b�F1\,l4�5���p�f�F3\����h9�5��b�1��k�5���p�a��0\c�1rv�Kv�,�+���b���,�+���b��.`v�d�:�4 d U R�L�+��*�3�����@&�3�Dތ�E ��� ���D�X"b�du27��T�f�Lb��u3�K�^j��$F�D���$_`z���}�^U�W��o��M���Jw�Ţ")ܓ�S���a�L����(#���:ʹ�9Q@AP�APFԚý���v~u;{t�dd���m4�)+�� �
�� (S���8#ԣ
��C=��~Ֆ�d�/ԓ�S���a>?ʀ���TW��.Ɛ�~oF;���_��/�mog�zT�u��h�B�d�h��I�n�w�P����*If��!�U�[-�3�����J �m�@�x	�d��Ta>u��O`��j1
a��0�*̧����C�zV�[pOCh������ A�7Yԙ|�h��ix@6��	3��� �
�� M-i��M4�)|	?Kb�{��Q�zԡ�Lb����~�Q��g�$4D	5G��|a��� ���DbF�$��l�J��*�F*3V�aPFTAuD�3$�'$�$�$���F!(Ѩ��Q ��� ��G�7�|�^U�W�e��|����½�p/b��N��B�	�V?�QT�2��*��`&�V����Pk���B%��
U��a�NuU�US�K�:ٌ���e��ERy0Y�ad�[��V���dŚ ;'�U� �UAP1��g�2 eAUT�L2����fcӅM�)l�$a���<5L��:�|\��y�;�k6���A��� �
@� D�l��W��V�o���d�P_�ST`v
LL�9)0�U ��� ��r.:a�,˄,Ʉ,Ǆ,��5�f t2�������,Dd���U�G����2d��%C&Ȑ��:��!;�AvԀ���P��H�xY~g��P�� �x�$�2�J~��7${Ph؃����(a�UAY"'BdD�|�
N	ʈ�BZ���_�y�?�=Y3��hG�h���vz
ۿ��V��^�����˕���j��*i�� 7Rz������!_k'��ۆ�b�|�?���;c�O�u���@~�;��I<�7K�Ʈ������ڟ�9��B�]?xz���h��}'��gg�^�>���-o'�_y�ײ��+��Oj��*���ɠbp�`�(�F<C���>,/ /��~r�M�_7��?ķߎ�>�]l�x���
s���W�O�Y@�o�7y�!4����#T���e#���Q$�qL���m}�ȯ���0����C��f[�!!("�i��F�����E>^��4������3���96�M�ס�a ��o?@:��Y}`>�����QH.�է��`�1�I�ì�x	DM�7�D��V4C:��l������bq� �:猡����` �Q���v�-����ᩢ8\q�:�M����B���u�r�MXnĤ@�A���z�m(�
6=迅2�k�x��B��׋��D��g~&�b�?�$H�,����!��	қ�r�N��f�msZ	���k@t%��\yE�����fRhp{a�u��(f���MEi8��"H��1ϖ���cYQa��۩�ߎՂ��1��{v�*��
���!L�3 94�!�5x�=&�!6,��1oI��9#�(ʗw��X(�B�#>��J�a֡��p|f��Y�a���DRX��1L�X�B����0S�t��W(����0k��ֲ�e�EH��;��i����|��Ц~e1,��!+t|h�!�U�1,B=��a���5Zm^�E��N�&��Y'Ӹ94��c�	�	�!�54,�x"���]��fX��cX�q���jQ�Q$F
3v�!]�zE��"��cX�~+��oźaBy/6FH����S���tL��#��v���Gh��Q���Bǰ����~��C�7�xC�޿+�N�P_1Bۋ�^,�&����0C�1-Fh1�X#�ׯo
	�%������n�Y�ׯ���u���c�"�C��a�P_C>5��Gzh�̻=C���f��W�<d�u��P�"(�����u��!�nmO��q�0D���Wj�����O���C݌���r#_�5F�_cYb���whX>5F�?�q�1E(�)l�P>S^3ɼ�'4�<T�U�1<���f���b�:ο&kGYg�0~M��o_�
�h��F��J�_�B��T�8J#�(��8�`��Ďv�3���+�3��[x���1���¨xjF�8,,���>V�V��z�
�X�
��̎�:���qq�^�ltC�˟�c6vv<����ƌo�3{��xf�K`6�%�����	�V��`��B�?�P0�ӧ`v����Kd�_�$f�=���I�vJHf��xxc��&Ϣ
��o��t�?va:�.L�}����_]����L�4ve��rW�#�J&�*�,���u}S�>V��t��S�޵;��K?�2}hl7��uc���n-6��;�=vgz��C��K6�?ك���=�<~K��r��ilN{=��c��l�x�'�#j{2�޵��kb/&�-�����d�#���+70�7��_|&w��0Ys�O����F&?��,Xx#���xL���ۨ�l<��/Cs��q��o��ﭾ�=�n��8o抍������VN'�9�$�9��3�g3�:�a�����\��3Ug�8SÝ�>3�k�ټ�;Sټ����ܙ������w5�<3�k��\�R֜�j� �� ����̷�yK��0�LM�>�����5o:Sݼ#w4o?S9�L*)�M�I4k���-�V4�8�m�g�X.9� e7�̂�pV~6gp���/2z�$�#y�A�s������f ���[u��3:�T���W6�⚞l��x�� ׸�鉦9�;��\�T��T��vpM�u��`l����w6nk�߸�k�߸����}��PSUS
��㊌�:� CU�ZjE+p��(������Fz�,d3��j��i��$�0�`�g���� �<�L�"H8�p����8�!����� ��*y^��t'^��e�V?��|��擯��}r/wr��'w�[}rwr����n�� r���8���[s�܊�[On�
=	�M�/�����(lA���c�鍍�kA����. �'�.8���Sg�1ou��3��]yvA?ݼ��B�Os���3�A$�=�F��${- A�>����:����yיJ��U�z.$!=�.�_d ��0��yH�� țwA����,��Ƚ�`���`�8�x��� BGA�A]
�"0�t�a��V��Lz`CIDv�Oo!�^/!#6�s��$`�2�l�yVKyJ�\jƏ�B�	X�������x^�g�Ņ�U���� V�i����Y��)kk�s��ӟ�Cl%KJ	��:�j6��n��n���x7�n�yfó��d��XЋ�U�ݰλ�V�=�t�w���\�ݰͻ� ������*����N�4q��i	�D;t6�,���bl�b=Ęh�\XM��z�Ƚ�:>�x��oǐ�^��������h���0&O?s�i���kO�;�
wz�����N/�N/:���K��gO���^�βӫNo8�*��O��N?I�@������y0-Fk� /�~q�:諾��s���ѳ̻
��UK��yW�A���&��
�e��|�R�:�-45��+�yW�`1˼��,pA�cFpyWm`�w������ж6� �a��.����о9�NN_�ݎ�ї�<��0F�={�Z�g��~�N�ٯ��!(���N&F+w�`�	F�z�S4{�A<�@-
��]CsȨ���U^^����7�-��9�¶������sP5竝˿Y��L~���霅V'�k��8���aR��N���sR)H�`vB�M��<VP�@��9ʆp�Q�;�<M��a�d��}t��Aǃ�Q$h�v�d�fI\�
_��B��p�V�f9l"̄|������G���7���xka���5@���l{�����Vަ�ߨ����l�:z�0�aF�h-J��Ҏ��׋�S� �Va�����(ZF��[��=Ը�kz�]��T�T	�>0v��Ɓ�D͟�\�|�ڍ���v{w���Z�ݵλk�w�!��ݵ��:�ݵʻ�o���
�
6��Yo;����S��ּSq����g�g�ٳ٦/��z��vzv���U/�W��(��(|�j� �A~��%0�J�2�#�LVѳ7��o���\���k�旅�M������<�
9��E����Y_��p�0�*p��Q���5[���0?t���z�9��zVJ g�b9��Ы�ksV�t's��GE;��D*����Jy#�.�x6@n�f�g%���[�y�ʳ�y@(�I60!i`7�g�g���9�`p ��=��@��0�,���2-h��oϫԄ��%;�%������%�W�0y���,��l��h�����^�4�4�q[��\�ډ2xOc]��"���6�5U6�i�j��׸�q���l5U�Uӂ���xG��q/�T����� �A�SMs����b
)W�kQ�vS��V*�j�[�9�CΟj
-Td�Q��&\u��������4�mf���_D��#*�DY:A�����K1�]��a������1�z���c6����#�U:��]fu��6����,40w�)0���Gk��3�xV����e%�1:����%�����x��.W#r�f1f�Y���� 5�TZH=�֭	W�  ����ј��p���Y��2˳�q-L��^�ys���4�^�i��^:����
�n�\|^�6-�>���mة���1������o��3v7h���u�*5��i��p��ht�G�@����
\J��1�m�e��T=הL�jw�HV��
A�P\Y=�l���G_u��� �rf�8i�:�-�[���,�nY	���wpĖ�g�� A��»e�w�<���-5�-�Їiw0tOR��\�[��n�Ơ%47ô��ߍ�����ܶλ}u!ö��z�-c�U�m�0Cw��x�m�G��/�%,r+E�Ż�}Ø5t���ֽ��;�[��[���u޺�޺W�{x�6P�bLS��[����@�]޺�Ի���u�4�3����
Z��{+�@{Yܴ�P�-޺=~��,i���@(�r
�J˶�v��%���D��&��/�^ֲ�RlЅO�vy��ܻ���-�����NJk)-Ty>��2��Ŵ3XSl��9߻��l�w.���n��-
��a���!܉ef�e�&�Kq�q-�K���sM�5�A��`�ܦ'������MUhK@�:�q(چ�o*s ����R��Lu��5�E qN�nz�qG?r��삏�q��5Ώ���A\F�	!p����|��5O���y�G�>�5o�Eγ�Tpg枭�80i�����wP3lS��������4ЈգST�N	To\1{^S]n�J'������+��v������g!ZE�ق��-y�J#O�s����0zV#��^�+TkO��kX��^���O/;��ú�����9�;�<��s�_�,�p�j)[��v,��g��]��l<��=���\��6��h��ѳ�������_�����'_���U-s|^W���U-�6~~���s*;M�E�k��u���%��~�-���2"C��9j����P�P�����,��d�,��6�K˜�,����?���?�0���K���I�	�bK��a���jN�r9_��ԙ3�A6�vp�P#M=o38,᧓�|<���7%�ݫ��ˆ\6�^svv��aR�|�U*��~3�.3��>�Ȏ%�����D<I�����<1������mc��dgw3��$��c��rۦIvF�d�5�d(��8�D-E�q�A�dZ�XR���.0�S���E�E�(��X�ڢ�v��_�a[��{ν$E^ROˏ$�̍�s�}�{��K���"�>�? Q��v/�k�õT�Ι/!���
�
������@
$:}�3s�j1$>W��O�!9�	�̩�xv/��׍�8߿�XK�cǏM:B�
s�p`�9�����<R4�����TP�!x�/��z;�C�t|���l�ínowx��eӯd<�_�x��SӨ�RgP���DW�|H0����1|�@��������nsX�C�T޹�yb뇻l���:��<ʟ��|����
��#0�@���mљ�&�oJ{���Gw>�����wA����ݍ���z���p��u-!V|߸9�8�H��3��{./Q��Mҩ UE�=��7�V��7	��Ǣt���:ЄOZ�čjY)H�5YC{}<N*��-D��ڞ�"�N�oڐ� �A��0�������4'H��Cb��Oz>�	���g������p�����s��L�yx��l�sw6�ޞM<�gϽ��{�^��+ʹތ:�3�㦳:���wk��l�y8��ܽuo�|x��L�u����òf����SN��Zp"x�z�sw&�t�Ç��w�
B���rG@8n�wg�ww�>�M<��$����c6�?qW�h�mR3��^�j[���AL�F�v� ;z�1��l�0k�&�F�jYv �NS��١��*����?���C�N�w�k�z��q�r�/t�Խ���Έ�������)x�t_T�v�nh��*2r�֝H��"Ky꿿��s��h��ك�6���� E!d��_��)�<^�+T��zC}׳�6I5dә����A��,Xm��z^����kL��<��e8B��
А�%��O�����z�^�D�0@��	�A00�	�P/mP4?�&���Ӑ�J�-z�����{�º�1�:�x���~횐�u���  h�P2�OG�܀g
�����wF�ٖd�����F��M�EA�����f�W�Hz��d򈬀�ÆdWΖ������UϤ����a��PEÝ>�,$8i�Ekw��.W3~�/lۮe	��pcO�T�=tP�n�3�5������c�������{�{wS�){�F��ӽx��H&\_��y�����^ޔ���6����1�
�Ұe��M)ή{E�{�P�G��"��u'�����^��A�T��c����}q�ё����+gT��U�"Ӄ2JV"�>`�Nc
RQ��]�Ϯ��T\�ܑ�*d�C*%���)�fu�=k��r�R6$��!S֮)PI�L����l�r>��Cۄ���Y��F�
b^�_��
���^�ǡr"6N��G�P2"8��䴤A=v͚�8�! ���kx���GC�d4,��䃲y�`5"<Z)*
2i�mq����,���Y>ʴX�1Κ���
�VE��w�*[%UV4۴8ѐ��
^�\�N)�"6-�m�q�9�rd/"���E���'�u;U�"��
1S|N+(�P �P@ED`Q�d�+�kN�(z_��~Y��4�$�^ϋ�S0�FKǮIF��d��9�Pt�F�gѼ��U� q�����*^�b�)Ij�	;Ou/��6r���s <��x�r�]^�U�Ee��h�
+���ꭘ�f*EI^S���چ�c�\/��2��Nӂ���b)'���%��p�P�PH{��▘> �x�7S���J���~��Ԑ>���6>�����R̊���e�hi�bE�2U�-z�֡2m�~A��c�`�
J�!a�t�\Aƾ��3���X���r�FA����q� ���} 88��D`���'�p?���M��)}8ư=��@4�8\:xp�.ˊ*���Pıl=�X{�oj��[P~�b�Wt]�
-��
�C2-f6"+��=��I�P���oKբ���6"��!ٹ�� g� ��L��9���<l�b����Y���@h#�'b@�L��z�z������T�@���A#L���9��L��u���
O:��Aw�j���B$eMU���h�%� P���T�4m���0�Xֈ���EE�mˎ�ؔ ľ!�T��t�d,oT�P!؊���V^�@���E����h$�LgrQ84l����a�Z����wg�b�!t#�ojp���05��P����T�H��3��^����(q�H������^"�v���#YiD�*ʧe��Ѳf�
�GM��T-�iZ��v��T[,�!��"�M<����nl���qq��F%����%pZ��Um�$U�Q�*��m��a6i[����HU��vˈ�+ �FZʮ���N.��i�l#�L4`�\ mg/O�4�ƸY&�N�x���� ��0�]��c��D�Y���ի�`��&iY�����J薍7�k��-�ykaA�m�G_ #)$8<R@h���X�
���
YR8f�r��&K��k!4��QhD]�P^O� oHZ��CQ�r�0'�$�r��rF�Ƣ{��
	#V��JU�\3���ٶ�w�-.� ���n�&[����ι�@p1]V�Mbu�����)� �AUü�x)z�o�5	=膴U�3~�-��{���)�Y�`.q�Hc*���M��"N{��
h�0��w��g%9���[�\9D���C�K�] ɗ�[���+��y�,�E�Dd�\&W���WI�����:��&y�| �&�!�%�J~��{���o �{��&�F~�\'7�M�}�y��2ٓ�"��=�_!��m�!�C��ܮ�{�>y@����#�|L��ߏ�S��ǥ_��'���8�d�D���:�MR�)ـ��@�D!%���A�̟�y������������������������������������2��ϼ������������+��\��r�/,�\\\L�[XZXZ��%
L��x����@�����~3s��&/�a�'G�
      const int other_index =
          CheckedDowncastToActualType<const Iterator>(&other)->index_;
      return index_ == other_index;
    }

   private:
    Iterator(const Iterator& other)
        : ParamIteratorInterface<T>(),
          base_(other.base_), value_(other.value_), index_(other.index_),
          step_(other.step_) {}

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<T>* const base_;
    T value_;
    int index_;
    const IncrementT step_;
  };  // class RangeGenerator::Iterator

  static int CalculateEndIndex(const T& begin,
                               const T& end,
                               const IncrementT& step) {
    int end_index = 0;
    for (T i = begin; i < end; i = i + step)
      end_index++;
    return end_index;
  }

  // No implementation - assignment is unsupported.
  void operator=(const RangeGenerator& other);

  const T begin_;
  const T end_;
  const IncrementT step_;
  // The index for the end() iterator. All the elements in the generated
  // sequence are indexed (0-based) to aid iterator comparison.
  const int end_index_;
};  // class RangeGenerator


// Generates values from a pair of STL-style iterators. Used in the
// ValuesIn() function. The elements are copied from the source range
// since the source can be located on the stack, and the generator
// is likely to persist beyond that stack frame.
template <typename T>
class ValuesInIteratorRangeGenerator : public ParamGeneratorInterface<T> {
 public:
  template <typename ForwardIterator>
  ValuesInIteratorRangeGenerator(ForwardIterator begin, ForwardIterator end)
      : container_(begin, end) {}
  virtual ~ValuesInIteratorRangeGenerator() {}

  virtual ParamIteratorInterface<T>* Begin() const {
    return new Iterator(this, container_.begin());
  }
  virtual ParamIteratorInterface<T>* End() const {
    return new Iterator(this, container_.end());
  }

 private:
  typedef typename ::std::vector<T> ContainerType;

  class Iterator : public ParamIteratorInterface<T> {
   public:
    Iterator(const ParamGeneratorInterface<T>* base,
             typename ContainerType::const_iterator iterator)
        :  base_(base), iterator_(iterator) {}
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<T>* BaseGenerator() const {
      return base_;
    }
    virtual void Advance() {
      ++iterator_;
      value_.reset();
    }
    virtual ParamIteratorInterface<T>* Clone() const {
      return new Iterator(*this);
    }
    // We need to use cached value referenced by iterator_ because *iterator_
    // can return a temporary object (and of type other then T), so just
    // having "return &*iterator_;" doesn't work.
    // value_ is updated here and not in Advance() because Advance()
    // can advance iterator_ beyond the end of the range, and we cannot
    // detect that fact. The client code, on the other hand, is
    // responsible for not calling Current() on an out-of-range iterator.
    virtual const T* Current() const {
      if (value_.get() == NULL)
        value_.reset(new T(*iterator_));
      return value_.get();
    }
    virtual bool Equals(const ParamIteratorInterface<T>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      return iterator_ ==
          CheckedDowncastToActualType<const Iterator>(&other)->iterator_;
    }

   private:
    Iterator(const Iterator& other)
          // The explicit constructor call suppresses a false warning
          // emitted by gcc when supplied with the -Wextra option.
        : ParamIteratorInterface<T>(),
          base_(other.base_),
          iterator_(other.iterator_) {}

    const ParamGeneratorInterface<T>* const base_;
    typename ContainerType::const_iterator iterator_;
    // A cached value of *iterator_. We keep it here to allow access by
    // pointer in the wrapping iterator's operator->().
    // value_ needs to be mutable to be accessed in Current().
    // Use of scoped_ptr helps manage cached value's lifetime,
    // which is bound by the lifespan of the iterator itself.
    mutable scoped_ptr<const T> value_;
  };  // class ValuesInIteratorRangeGenerator::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const ValuesInIteratorRangeGenerator& other);

  const ContainerType container_;
};  // class ValuesInIteratorRangeGenerator

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Stores a parameter value and later creates tests parameterized with that
// value.
template <class TestClass>
class ParameterizedTestFactory : public TestFactoryBase {
 public:
  typedef typename TestClass::ParamType ParamType;
  explicit ParameterizedTestFactory(ParamType parameter) :
      parameter_(parameter) {}
  virtual Test* CreateTest() {
    TestClass::SetParam(&parameter_);
    return new TestClass();
  }

 private:
  const ParamType parameter_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactoryBase is a base class for meta-factories that create
// test factories for passing into MakeAndRegisterTestInfo function.
template <class ParamType>
class TestMetaFactoryBase {
 public:
  virtual ~TestMetaFactoryBase() {}

  virtual TestFactoryBase* CreateTestFactory(ParamType parameter) = 0;
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactory creates test factories for passing into
// MakeAndRegisterTestInfo function. Since MakeAndRegisterTestInfo receives
// ownership of test factory pointer, same factory object cannot be passed
// into that method twice. But ParameterizedTestCaseInfo is going to call
// it for each Test/Parameter value combination. Thus it needs meta factory
// creator class.
template <class TestCase>
class TestMetaFactory
    : public TestMetaFactoryBase<typename TestCase::ParamType> {
 public:
  typedef typename TestCase::ParamType ParamType;

  TestMetaFactory() {}

  virtual TestFactoryBase* CreateTestFactory(ParamType parameter) {
    return new ParameterizedTestFactory<TestCase>(parameter);
  }

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(TestMetaFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfoBase is a generic interface
// to ParameterizedTestCaseInfo classes. ParameterizedTestCaseInfoBase
// accumulates test information provided by TEST_P macro invocations
// and generators provided by INSTANTIATE_TEST_CASE_P macro invocations
// and uses that information to register all resulting test instances
// in RegisterTests method. The ParameterizeTestCaseRegistry class holds
// a collection of pointers to the ParameterizedTestCaseInfo objects
// and calls RegisterTests() on each of them when asked.
class ParameterizedTestCaseInfoBase {
 public:
  virtual ~ParameterizedTestCaseInfoBase() {}

  // Base part of test case name for display purposes.
  virtual const String& GetTestCaseName() const = 0;
  // Test case id to verify identity.
  virtual TypeId GetTestCaseTypeId() const = 0;
  // UnitTest class invokes this method to register tests in this
  // test case right before running them in RUN_ALL_TESTS macro.
  // This method should not be called more then once on any single
  // instance of a ParameterizedTestCaseInfoBase derived class.
  virtual void RegisterTests() = 0;

 protected:
  ParameterizedTestCaseInfoBase() {}

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfoBase);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfo accumulates tests obtained from TEST_P
// macro invocations for a particular test case and generators
// obtained from INSTANTIATE_TEST_CASE_P macro invocations for that
// test case. It registers tests with all values generated by all
// generators when asked.
template <class TestCase>
class ParameterizedTestCaseInfo : public ParameterizedTestCaseInfoBase {
 public:
  // ParamType and GeneratorCreationFunc are private types but are required
  // for declarations of public methods AddTestPattern() and
  // AddTestCaseInstantiation().
  typedef typename TestCase::ParamType ParamType;
  // A function that returns an instance of appropriate generator type.
  typedef ParamGenerator<ParamType>(GeneratorCreationFunc)();

  explicit ParameterizedTestCaseInfo(const char* name)
      : test_case_name_(name) {}

  // Test case base name for display purposes.
  virtual const String& GetTestCaseName() const { return test_case_name_; }
  // Test case id to verify identity.
  virtual TypeId GetTestCaseTypeId() const { return GetTypeId<TestCase>(); }
  // TEST_P macro uses AddTestPattern() to record information
  // about a single test in a LocalTestInfo structure.
  // test_case_name is the base name of the test case (without invocation
  // prefix). test_base_name is the name of an individual test without
  // parameter index. For the test SequenceA/FooTest.DoBar/1 FooTest is
  // test case base name and DoBar is test base name.
  void AddTestPattern(const char* test_case_name,
                      const char* test_base_name,
                      TestMetaFactoryBase<ParamType>* meta_factory) {
    tests_.push_back(linked_ptr<TestInfo>(new TestInfo(test_case_name,
                                                       test_base_name,
                                                       meta_factory)));
  }
  // INSTANTIATE_TEST_CASE_P macro uses AddGenerator() to record information
  // about a generator.
  int AddTestCaseInstantiation(const char* instantiation_name,
                               GeneratorCreationFunc* func,
                               const char* /* file */,
                               int /* line */) {
    instantiations_.push_back(::std::make_pair(instantiation_name, func));
    return 0;  // Return value used only to run this method in namespace scope.
  }
  // UnitTest class invokes this method to register tests in this test case
  // test cases right before running tests in RUN_ALL_TESTS macro.
  // This method should not be called more then once on any single
  // instance of a ParameterizedTestCaseInfoBase derived class.
  // UnitTest has a guard to prevent from calling this method more then once.
  virtual void RegisterTests() {
    for (typename TestInfoContainer::iterator test_it = tests_.begin();
         test_it != tests_.end(); ++test_it) {
      linked_ptr<TestInfo> test_info = *test_it;
      for (typename InstantiationContainer::iterator gen_it =
               instantiations_.begin(); gen_it != instantiations_.end();
               ++gen_it) {
        const String& instantiation_name = gen_it->first;
        ParamGenerator<ParamType> generator((*gen_it->second)());

        Message test_case_name_stream;
        if ( !instantiation_name.empty() )
          test_case_name_stream << instantiation_name.c_str() << "/";
        test_case_name_stream << test_info->test_case_base_name.c_str();

        int i = 0;
        for (typename ParamGenerator<ParamType>::iterator param_it =
                 generator.begin();
             param_it != generator.end(); ++param_it, ++i) {
          Message test_name_stream;
          test_name_stream << test_info->test_base_name.c_str() << "/" << i;
          ::testing::internal::MakeAndRegisterTestInfo(
              test_case_name_stream.GetString().c_str(),
              test_name_stream.GetString().c_str(),
              "",  // test_case_comment
              "",  // comment; TODO(vladl@google.com): provide parameter value
                   //                                  representation.
              GetTestCaseTypeId(),
              TestCase::SetUpTestCase,
              TestCase::TearDownTestCase,
              test_info->test_meta_factory->CreateTestFactory(*param_it));
        }  // for param_it
      }  // for gen_it
    }  // for test_it
  }  // RegisterTests

 private:
  // LocalTestInfo structure keeps information about a single test registered
  // with TEST_P macro.
  struct TestInfo {
    TestInfo(const char* a_test_case_base_name,
             const char* a_test_base_name,
             TestMetaFactoryBase<ParamType>* a_test_meta_factory) :
        test_case_base_name(a_test_case_base_name),
        test_base_name(a_test_base_name),
        test_meta_factory(a_test_meta_factory) {}

    const String test_case_base_name;
    const String test_base_name;
    const scoped_ptr<TestMetaFactoryBase<ParamType> > test_meta_factory;
  };
  typedef ::std::vector<linked_ptr<TestInfo> > TestInfoContainer;
  // Keeps pairs of <Instantiation name, Sequence generator creation function>
  // received from INSTANTIATE_TEST_CASE_P macros.
  typedef ::std::vector<std::pair<String, GeneratorCreationFunc*> >
      InstantiationContainer;

  const String test_case_name_;
  TestInfoContainer tests_;
  InstantiationContainer instantiations_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfo);
};  // class ParameterizedTestCaseInfo

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseRegistry contains a map of ParameterizedTestCaseInfoBase
// classes accessed by test case names. TEST_P and INSTANTIATE_TEST_CASE_P
// macros use it to locate their corresponding ParameterizedTestCaseInfo
// descriptors.
class ParameterizedTestCaseRegistry {
 public:
  ParameterizedTestCaseRegistry() {}
  ~ParameterizedTestCaseRegistry() {
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      delete *it;
    }
  }

  // Looks up or creates and returns a structure containing information about
  // tests and instantiations of a particular test case.
  template <class TestCase>
  ParameterizedTestCaseInfo<TestCase>* GetTestCasePatternHolder(
      const char* test_case_name,
      const char* file,
      int line) {
    ParameterizedTestCaseInfo<TestCase>* typed_test_info = NULL;
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      if ((*it)->GetTestCaseName() == test_case_name) {
        if ((*it)->GetTestCaseTypeId() != GetTypeId<TestCase>()) {
          // Complain about incorrect usage of Google Test facilities
          // and terminate the program since we cannot guaranty correct
          // test case setup and tear-down in this case.
          ReportInvalidTestCaseType(test_case_name,  file, line);
          abort();
        } else {
          // At this point we are sure that the object we found is of the same
          // type we are looking for, so we downcast it to that type
          // without further checks.
          typed_test_info = CheckedDowncastToActualType<
              ParameterizedTestCaseInfo<TestCase> >(*it);
        }
        break;
      }
    }
    if (typed_test_info == NULL) {
      typed_test_info = new ParameterizedTestCaseInfo<TestCase>(test_case_name);
      test_case_infos_.push_back(typed_test_info);
    }
    return typed_test_info;
  }
  void RegisterTests() {
    for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
         it != test_case_infos_.end(); ++it) {
      (*it)->RegisterTests();
    }
  }

 private:
  typedef ::std::vector<ParameterizedTestCaseInfoBase*> TestCaseInfoContainer;

  TestCaseInfoContainer test_case_infos_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseRegistry);
};

}  // namespace internal
}  // namespace testing

#endif  //  GTEST_HAS_PARAM_TEST

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PARAM_UTIL_H_
// This file was GENERATED by a script.  DO NOT EDIT BY HAND!!!

// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the d�����Ք�Zַ�oW�I?M����۝Mظ�m�t|R�I�h�frw�P�G���j�a�#%d�j3[H�O�ؤ*e
����g>��B�w�������A�_��	�$��<</��Ex��Ӿ� ��+��	�I�Xy�@�M~�<o��$܁�w��	�$���}z@������A�����g$<�Q&f�,�nIx�"���\L�e�<yV �"	/��qjk_:� ��2y�BBU�^�<k�P~�!Ϻ$ԃ�Zx�G|��F�1y6!�)	͙�[8g.�Zó
�A���2�`CIF�p^#a$	��`"�(8)����Q$$�0��D�D�SH��T�n'!��2!.�<�$�-&��6	�H�L�@�i�ǻ�}	36���F��'�sI� ��\H���"�����%$|D�2&�c���<sP�
򾊄�$�!a-ĭ��F��L�Vv����](�n��k/������@����v�<���	�<I�)N��4��`xI~E��$�'�	�"�K���U�F�u�]@�ߓp���H����$��x�
�w��y�N�=�]H�����y�����x>$ϿIx�)��=%��24�}]�?_�GBI�I(�eɳJW�W �Ix��J$T&�*	�H�NBMj�P���$ԃ�Zx6 φ$4A<�2elF~7�<[³5y�!���^:��I"!����.�C��a���w'�u&�]���w�I�EBo"H����ُ�WI�O��@�����z��C	6����	#H)��:�M$D�`&!�b�8�{	�[�3ޓ�3���ӎҧ��8��$!~�I��I�@��$L$a	�I�J�4�{�<�E����$�$a	�Ix��9�<����O�H�~/"��L���KIX�r�\�+��֐��[O�7����[�޷�s;y�B�{��~�~��OI8�����(	� ��<O��I�<E����y~IB>	�H����$\$��%�2	W���~�<�#�	��$�r��&�	�I���;$�F�]~G���{!y�I�}�"�����?&�		OI���g$�K�s|�P�<�H(	�K�gixw��e���L��Hx	p��;�J�= ~W�gU�NBMDW�ׁ����6����C�����4&�MHh
X3ל�Ւ�n��6�,ߤ@�ڑg�&�!$t$������ :z�޻��蝬���$�"�7	$��H��h_%�Q$$a(����5F��`&�4����9�i�x�;���9��3��l$��`���e�ǡ�L���D�x�>������ lyN&a
	�Hx�C;���9��#��$�a��'��0������!���s		KIXFY�J+IXE�'@��<ג����$l a	���}����� a'	�H�M�^�p��C$&�	�I�ҞD<N����y��/������S��Y��nz^͞�*N���`���]����X�����
���y�o��*�����y����]�|g�k�WV�����v�L�߾j�M��.���fy�:�6���7?=�U3K��pǬ�q������~�Wk�J��i��T�k%\z֥�ߘ��vTn�a\���)uOlm3�#�	�W���j�O:�]��v���Y#�Wf:���
'�uoUr����I�K�����-����7Zݺ;Ѽ�'K�%����C���p����G�4��C�����R̈��ӎԜ]k��J���JK�
���Kg�|��|�`T�����C\�w��+9�Aė��mu��sp�O֎������;��rt�r����ǦU����<�� ���>lW��.D�7'd��k�8�zl\���_Ƨ&�9��.`����eF��������7O,��aҭ�Ã.�ڵ��Ŀˮu�/����fUn_kY{֜��.��1'���Ο-�?�ս�I��5o�2{n�[Ϫ��X��O�"��
+QcT���?|{��qFk��!��Z3��Ѽ:)�i�V�����A�KGV�8�g���M��_��j_e�)���3ƽ��ި�ͿR��/�ߏk�$�̉#�?��s)s}�k��]�Y�����+=<�o#Sp�S�|?m�����>��ܴ_�>0k����:�����J��������{߬�rY�
��p����Kӟ.:_zL��v}FF~o�Un�Y�ܰ�IVe������#Ƈ^^:k���S�]x4����x����Vs���~ޱ�j@꺝ң��t�׶U�7�%�X�aĆ�.����GO���ڡ�%o}v����i�ذnç�,������)�<����G���lY�=d��_N����w����Yg�
3Fj�����ҳ�����J롕;G��ޤc�;Տ����?+������7VN���፟_�����m.�8���ss����Ơ����=~��oCύٞvE���u�����c_�:kyZקC��d�|���3ǖ��J��%��Ȏ��9Q�!uWWX��o��K�3�n��v���g�.|�3��V����t��F/U�]}�՚a�����zǧ�?����c;[��n����=�K�Y�cδ�?W[��߯�m����G!���]Vݭu'o���������_{� S룃�ߏ�\����ّ�K�������.'^�}��0�C�ɭ�ݳӧ�>~����s��/_�V�w����:��sa_�J١���o�����{��z��oS��������u.o9|��J�����y�������v\����o�9�ﵨV�i5���Uݴ��:.�}l��z%�:QB*#��N6�� �-���g��i
���y�G0
9��7�E��ߣ���`|	����I0ߕ��o
�ׯ������y�m��'�?����+	|��`\���������G 'Au�E�?��X0/�]#>�b<�P`�
�ƨ�|��UP���{9�^$�c�x��|��e9�-�g�(D�(ד�]/�3�
�������no8W�.����d��$�����n�x��a�<e��
�M�㴻��;�rr�G�>�2/�����	֭�l��6G���W��
����x�@�����+�xM��8-�o��QU���I�Xӏ�$�����<<�$X5�����2|��`q_`w-���A����Y�y����0K�M*��b������i��+��~���(��v��>���Y||�@o� ��>�ߵ��N�`�*X�Uз�	�ֳ�'N0.��yN��`=����{5�ͦ�����Y�@_	�R)�|�T`�n�{U�N�!(�>���O �#���,�
�,�=v���N��~{��@�_̃��F����`��_���T���
����(M�o	�m�`�h�S��S/�;�n����^�*�c7��Ym�`���U~�	Wu���a��='���a �\���~х�����J���&���=�$�?�?O�0�5�
�����H�8#X��;�VS�N� X�!�O|�浖��h�`=�J`�|&��(ׯ
�՗���`���a�`��'��	�PA����������H�7^'�W���>~V��b�^&Y0�:�����	�|TY��'w���`�u����»���
������T�������G�%�>�:t����R����w)�u{���~> ��52���ң=�nl3UN�}E��Z��/+x��OWu]0p����kX����ɿ��?�*�w����Xg��Qp��2	#������0����a1�_��/U߅�)x�M�O��<g�����i>�R���C��?\�W��$�w����
��L��
�4}ě0����N��)g�� �+h=���@$�_��/:ߕ0~`�P�k��K���Eb��S�K�7u�8������g�r�F���)A�Kz���́~iL�C�����>T}o�<"}K��`�ۂ:
�)��
����������O��4����e>�!�9����sy_J�sC�u\u�;6���ׄ�l��ǷK�@{JО�<����^�L;3o�>� �
�Cz���^vU_j�
����vІ vi}UO6�v?�j����L���C��}����& ^H��*����Rnz\}k�Hσ#��x�J뇵`Ge3v�e*襲
�(u] �vc7� >�����)�W[��cӀ��w��C�����;�hZ$���=?M�;�<]@��l�7�G#��%pԷ.m7&A;6�|��������]K>�K�_����࿲���ϛj��+���/�>YM��QP�{��I��6z���WX��Wø����S�=@���=�^_���6h���<�V����C@ok7�r	����?����I�U��/���\��5��g��F�^W���:�̳��i��/�W���y
�[���/�-E���������O��XM`�w��T�=�~Y]��t�F���N��:r�����*�E
����3�S��a���<��?Q`W��t���>'h�Z��:Ə�0D�.����|�
r�==�ۀ��;Am�Q������)�\U�}Rp���О�\Z_m�����O�}�/0��Ɗ��c5���FM��.|�!#?�B�g3��6��
�_e�2.r�v`CXG������K��&���Oh��i����֓���V��?��� ��~�A�.xs��+u?wD"��Z�ς���)���譴é�t;�uw4�� ƅq
3/�Rۄ�\+�g�~��r����N��ȷ'	�K�>�c�u��]��}��>0��0���	��s���������O��:_��>�̾�U�36�3�~A=�G��ǉ`�攤�S�_tW��Ճ���L��'Ly���'���_��P��{���U��������"`�%�9��K����W��ps^�؁��z�9��9�zM}����9X7E��m ���s������ݴ���Z�\�oP�|��à�s}h}��[z�6 �d-��e��#��� ?F~ލ�����Q��W7�C�Ka?+�W���G��9�9�W��&��
a�
����Y�sSAp�߸��w�����ğAj���d�?�[�2����9����h{&�4��z5�y-�!��'������v�-����?�������E��zm=.��|{�6�`a�%}B���%�C�r�<U�z.����uDY�W˴C%�oXMہ������>�_�-��S@�eC�{��{���f��B_��穌4�tXw�q�I�o�f��]���_����h�o��򄃞w0�_�?��O�_�0�@?��������UJ]���Ge�=u�h��0?��Bۥ�@o�s��`�l�F�m)�g�)z�_?���,;��9>�ژ����`�]��������|'�9��}t�
��e�`�� �f`�II�gr{f,�k����s�O6#?#a�J�85��Cˌ녂���U�w������-d��sP_��=�|�����nώ`������ ���i�U/П9��LE!s�����O����E4s���s�^���ZXoڎ��V��<���vvu4cWo�{��Y��篠�������J��g�}XP��sf��1viO��d`��
����H�=�����y<��h8��j�T�?�i�%������뵒 '���� ���_���r���f��+p�4����������������V��a?K���Aԁ{�y���yr�	z��
�"�-�l
k���=`�:{��_��i���C�̸��S?�����3��Z��*��c���~Ds�z��������.�L8��2��k}�s��3������O��M1���<I��P�������w�4Z���`�h���^}���G��&��SΫ8=�M�����
ƣ����'���i>��^�l�nZ�����-��~�~B﫿���n�.���:�G�1�%�)>)%�dO3���L�ɚlM�L��C2E�g���Z��4K�~�S�-��1�%�c��4;��o��}2LQ@�=�l�[��W��������ii�֘�4K���.����Q�u&���Mf7Ŧز��|fF}�IF]`��K1){8+�.�bOKM�r6zf��fI��8�)-˔��2��<�]�H624ޒfJ˲Y�i���nS��"_
#dU|b�ޞ�z���8��gs�;���m(q�3q_�n�gD���{��l*6��xgs��[@�c�0|���&�a��ĔT΀Wp� ��K�5j��`��K1)=�⌋HN�k�B�\4P�EQ��]F�p��J�;=S�i��Qp� ��K�5��e0F������*Keϔ�{,o����^���/2_j��x��/�����:���b�Zj�I�F�Zmi֔�pP�,�n�j���8����7�+�^��EHM#�cDHc\�I�R��A�R�6��OQx�R�$�j1�@�KG����Y��ͷ
�)�2�X�Z�c�MC`k�G��hw)u��@�G���*�J��C�8\ݩ�H�<���)��q�iiiT}]1j^�9Ő�sr�pK-ԓ�����Ĭ
E�UU��foP���"�@D'Y���A���k�rځ��^TbF<�Z�s�YZ���6s*�ْ̩c��ΝT�K�I��HQDq�50�5�c
����e��8�m�dԼ�&(2S��� ���D�|��Ozj-�[Xح��W���]��UA�^�6�T,�ρOG��b0��k���T�(1�͂��HvQ��/��N9θ�����r�sslo�%Zc-r�V�G��X�X9��@�T=�M��fk�lB�3۠
y�M"Y��|���M�Ďqj!b�BĚ�il���i�]���^� g-]��u�s�&�뭦j&3s�����ēe�q.�]�R�pa�z�u	��bb����CM��^�&�'�Pg�9�9�C�$/�Vg�j�� �[�{6Hƣ���-iO���^eF�7�kg�s:�Sx�{�أ�\ZS�5���&�[Q�ze�c�9=Q8�	�V��QNB�!�"k)g��{Jb������rS��O��R6���Qa�h0����{'�?�����c&�;�urV�驩�����̓�P!��"<Y���LVJ����w��]���� ���k5S��9w�D�\g�
N��9'�Q�)I0�k�*X�K�GYF	�W�d�D$<����
e���mk�*ʳLԺ�]z"E%�G�`�1#�4a �����X
R%��YE*\y�#��6�K�ۃ�e ����]�qΪ�r �
,o��� �8�u�)�m�3���q�ǜy�'�9M�����X�"�g'Cל��^��KL1��̋9���=j�sׄ_
��būN�$n���|:�maI��W���,Ca��p�+�1��W#lU8kD["�j��jQ\���Ņ�Mv�Y�T�i?��,��Jc��,<ȓ�"���mE*u�)��c�Aba��2���9�8�
�X�1%:�<�Qf�Me�&�7�T28���WF2�>%&��(1\�==5Y��F�s�J���͕�í[�mcd��e+/Ʉ���]�G�4���9�[�*��69L�y%�3=,2b̆{0 ��s����"H��O�Rn
7B�pr
�z"p�Zc��jg�q�T�����eK�w��i!�>zA+��$�d܃�$�90��k��jNЋNWƴ�Of��Z9��5$�տ m m�z�D�z_����0�=�X�)2��(������4%��H���X�1��T�CJB��8kZ��#���?���c<*gN�!.01]Ҥ�yU⣮
q�ǈ��d;F��s
Rzk�0�6����L�i\�#Q����]0n��k���c�eDܼv�����
u��\�����k3z�'�e���fT��.n"*g�/1�E[/|M,��Py���f�3m[�y+�Ⱥ���嫙V�+Yх��E������1A_��1nq��-H�e�$�ً����[�ӓC���D�q
/���,��UL��/��k�c,i�
t{��DQ|��8��dW P}��`.x���pU��}�����N�Bnw��+ nf��`�&l^�Ɛ�9�\Ĕ�60E15�D��Iym!d�֣u�+��B��X鹄��(j^�qv,\!�j�k�\(J/��#K��p��'�L�&HJIN��̱|��:#-�v̅�✯ܓ
�ݐ�@�\$�:S};I��9K�
�?K�:h��t�_�w��m��r��
��x9'ƻ�R�@�;\�b"��E��	�?��,�K���&�^�ܥbA<]�F�4�8z�>�Y��pɲ�"���q�����Aeo����������S[�%ױ-��<g����W0��fH�2�����T�~/�!�A�2d=���^b�^cŧ�)�D@�a�#�ߠ� :��ɸ�bL�9�2�b/�cE���X��¢�y���xe".���͖��iM�GM�9�4����d\za!l�8k<�u_ �@������*�-�n���xd�I+�ݎ�OK�ƎI����a�"�����.=��{�i�QA�8c��&�bU?�<��-��u�#9.ђ�4�2R��S����](W*<7;}r/h��$\��9�xXg*ȱ��|XTl��c4��	���S.,�S�"b8����~�.ٚ>0̄��g?����â�����s�&;=f$��C�ľ���$׿y�ǁb.O1S�bzJ��MɊ�7��B�k5��G"CO>e�5��$Ezj��7���<���Xx$JM�>EC�̅�r�H��|jՍӳr;9��%��?�1���"R#�a�4P1��yI������7D��(V>��D���:?C��E��y��P�cF��B����:Q���2M)�F9E�H�,��uu�I���οb�lN̲[]g��cD
�|T�8��&b�/�9�FQR�KV� ��#�N���`ȷ���,<�cEg�?hW�ڼ�"�-��y�rg�\���^�>ђ/�z!ܔ�kO�¢��OW:w�2��k/37q&r����"2��Fq�q���Rv��\�z4�~��l�x�y���+�!��*�!̬�h�����Ƣ,�c�̄��n1X��.��G�I�-�_�"�r���\�x�g��+��T�xg;(������P��0S�xz�U��JM���Zê����~�S��|X�x���OΧ�d�h�c�i�$f�:o�3#T!��jj�	o���d^�]b�r�ǃLƜޖ!�Õ2&���q��bV��g�r���dA�T/�&(Μf��L#6�ɹ��LB&KjjJ*ܘ�"�E��+�bK��e7�k�="6|���_x��|n&<*)IJ�$�ڲ����k-8t�~]I	m�A �>����&<	,"Z12�{-�x�כ�l�d����,@2�ѿ�TɱdQ���`c�%Zrz����!(����Zt �����C���#>=������"���޽NtE�����E���H��� �
�� ��	�P�_$©�����7�8�w1����|�~��ɣ����U�q���Y�E'r�)ؚ��g�C��ghAFX>)��Y_sVJ��8�+)X�!���c��f\�!I�h��w�\�!ו����łM�?�}�p�����T -r�T:�=f�G��Ä�|r�،�-���bc-�;*�v��d�]
7cZN]_�u��z��*�V���
e�w�ʝ���}n�s����(�K��X=�,�d�g�+hf:�2�R�w��g3㕎�s�	�������dnm���T�Dk|�l���_䝳��o��ĉ.�ɛI$��oS�OL�ڜK]/�,*���*j�XԨ�|hʢ�:�55��`U;=���Kh��&���2��my�yšd��PHB�����;Gz������A�E:��PrMJ��IԬ��������QKɂ�(`fe�b���g-��_jB�[�?�`w	O�����s�rJO3��[z�5`��Gϸd�h�u^��MIO�7 M���/�=$�	����PI��8�˄�������
r��uV;|;8�M����bL涋#jH�)�;3xeǭ��l�x�Q�a����Rr�Mv�,ן�CYB�(K5%'KqJ���.5���
}	Eucƍ���I8�|��Ȓ .%_����.j������:|�����,yȌf������p�GN�^5�E.'���	�)g�c��O;{�c��m|C0�7wU7�/ߥ'�$N����IW�(K
/n˻�Ͽ����^��Y�	�iR]���THYȺ��6�S����d�����b^���id�X�L��y�3N����J��s���-�-'�
3�h2�hq�Sc������xIeͭ�������<�+_�w��UN����8��+o
S�"\��� �������#KT�ؿ��̩�/�*��#L��7~���089��$�\�G9S�{c?нlM3ǘ�N�>ʎX���'\Ư���Ry�C����~��,2s��	��"3J���<�	�`����1��P�e��Ν���l�k1�UA�^(8����8'>\���]z	��7����i����2j����pPÓs�Tu5�]1%��$Į�L�,������ߩ_
��y�S2�b��*{w$�g�\��%�Z����Ԏ���7�[w���M�~
��X��V�S���]X�iה\��N�e-㴹4���s���o�}�3p�Ok>��iɴ��緎)�sC �nSj�v,񑟡n ܸ��O�0��<�\�YῈ��0�
�������7��<���L��a7+o
��c/���|��>�N�����5���M�kv��K<t��^������>� O���O	��|\w��g#9\��7��G|�� ���ǵ�z>}�-��o���|<W�w����x� ����p�� _������p�~>�/�m�x�A>���0L���K[�x� ����S�Y��^�go��<{;������v�q�.>����|�� �G@/�s��q�>� ����/	��|�p��� 9�����|�O��[�x� ��
���m|�� _���G���y<z'o���O��v��Bn�#��{�����ܱ��p�>��� G���W�e����6����zj:�����/	��k y��S��P<�
�K��V>n���9<w����'��|�@��v�q�.>�N�?��{��M��	���|<t�����|\: �G�A����-��\��B$�с#�?��6G��F|0^�����+*g!�����wE嬁�3�O�5��C�U�$χ�����j9u��!�7
�3��v��u��m�>�3���>�r:\-����:D��#���`<�;3�uh��W�]��������!�[�}�x�q	�k�!�7�w�^W����z#>���<_p	���c�yH��C�~���r6C���|��i��o�9�Ƴ}_T��H_�@���j9C���)D��5�q��\�_)�=�9n�E�����%�W�r�p��>�"�-l��z}����9��>�X� |,w���;¯!z�'"��1���uq� |-�s
ᝰ=��y��m����y���u�$�ؾ�k�:;�Չ��da3��sy:�������4��9��/������\����}�W�v�+b{	�/ay@���^	�E��z�W��«`;�U�}��jؾExu�@x
�fW��3{�f/����'��3�I���~��?�Wp�g������w���^�����p�g�?��3�Y���~��?��������3������"�f���������엹�3���������!���W������-3{�����̮0{ߗ����z>���Ϲ6��s�<��o�����&_�g�Z|�����p��F����0{gf����n��[��.�������������>���71���ހ�_g��|���̟�2{cfOe�&|��7��ۙ��\��oe�%�ތ�Sb�(�_�ٛs�g�����6�������o����wp�g����~'���N����[s�g����3{���~7�fo�����q�g�X���~�fo����;p�g�������f���?�w�����q�g�.����+�f�����{p�g�������f����콹�3{��������r�g�~����?�f���3{�f��[W����v���>��?�?�������샸�3�C���=��?�����C��3�P���>��?�?��������r�g�����}�f��?������Op�g����3�(�����f��f���ٟ�����q�g��s�g�1����y�����f���f�N�����r�g����3�?��3�8����
�fO��<��ErD|߭y�����<݀��}���Lr��Q��ڬ��1�D���-Ӊ�Du8���j�Y�ĴEC]�IL[3�/�Ӊ�@5<���h����1]z<���d�O���Vux1m�P{�����8��^�T���i�j�&����1m�PO_!�����V�u�܂8�����A?8��>�k���P����UpC�W7�~p���.%n��b�&�.$n
��Mķ@?8��V�g7����ˈ���N���i�-�<��6��$��~�t���B|;�'���q�1�C|'�G��~�p���N$�����@?�7����B���B���~p+�X�� ������C?8���kw�~p(q'�_�"�^�Ww�~p�}�.%���b��.$���M�ݡ�M�����=������Ӊ��F���s��@?x&q<���~��~��H����%��!N�~�(��N|?����@<�����~p���"��x�[?��ĉ�nL<����C�\�x(�C��A?��}��~p%�#�.#~����á\L<���ďA?x�H�g?��L�'��O�?��N'~
��iģ�<��i��$~��Ӊ���)ģ�<��Y��#~��c����Q�c�<��y�'� ���/B?�7�K��B<�/���_�~p+�@?��8�7&~����I��I<���įB?�bg��A?���u��O�~p)�D�O�~p!���D�&􃳉߂~p&����O<������~p���%�
����Ӡ<�8��S�߁~�D�A?x��C,C?x�t�'v@?8��=� N�~po���܅x��C��B?���nA<����gA?8�x6�k��P⏠|�^�C?�����ρ~p)�\�
��B�Ϡ���s�g�����_@�Y�?��N'�
��i�i��K�5�gσ~�t�o�<��[�O$���q��A?x���"N�~�p��N$^����C?�7���B���@�/�~p+��nA������C?8��G��$�	�������I�
�W��~p�*��gB?��x5���@?x����&^��L�u��O���t���N#Ά~�\���$΅~�t�
����۠܅x;�W���w@?��N�� .�~pc�_�I���5�wC?8�x�/v�����E�.#���R�b��@?���W�o"���l�ߠ�I| �G��~p:�!���B?x.�a��$>����G�<���'�~�8b��c�U��".�~�p�r�'��~� ���M|
��]�+��4���4�[���ĕ�nL|����@?�&�Y����~����C?����ˈ��~p)�E�_�~p!�_��D|����W��I��
�?1=�R�Ӊ�Q���FL���,�\bz��.�$�GN������IMO!�GL�d�Dbz���GL���'�c��Q�:<��!���É�ё��HL���(� bzT��������BL���ӧ���6��"���đ�nL\������\��&��7�~���4��~p%q#�����R���.&n��B���D|􃳉o�~p&q3�?��'��~p:qs����~�\�۠<�8��Ӊ[B?x
����H|���@?x��E�
��É[C?8��.� n����wC?�q[�?��'n��Vı�nA|���~p$q��$���P�N��x���\I���e��A?���􃋉�B?����7w�~p6q�g���r�?q/���A?8��7����~�L�x�O'���)���<��?��K�C� ��Q��<��~�'ۡ<�x �{? ��.�B��x�[?��ĉ�nL<����C�\�x(�C��A?�b,���\I��ˈ�~p)�p���~p!�c��D<���ďC?8��	�W���OB?8��)����~�\⧡ܥe�ѩ����WJ������A�Jw^����u^�IrD�k�-K�0�yp��Y|H��Z�}�����X����8@;�
���J�$���+=�jy��+I�Da���jk�i�˛��QN��;���gD�
�h�?�U�+h��U��fJ��z(�m�+�;НK�^�vGZ��ߖhM~똡�=�d��{];�J�HD�S�?���f��Q����j�P�c�x�u=����q"x�Iu<�c�>����X�U����b�z�t�p=��y=��u��=�O��1ʛ����Iz����RjC��z�7�l����r��;_��gj��� �f�p�k����x��~�(]�5��Dg�P���"�~��-��C��v�{�G��M��7jX�����+�q�q��ו�?���U���֌J�.����R�O�4z:N�!N>���)tٓ��\�oQ�Mצ��1������2r��~��C$��;�$��u)��Q�5��C��X�E
�(��ЙhC��~�@s����W�ş�6����DD�|_+��,��z����E������z�6qY�í ��h,nS%s�E]r:�~x@����f�n��"��X��+��fA�w<�O����z
�\_�B�a�6���\ú������|�r�rCm��pxN����_
�b���!(:�����ء���C��(�}�0�|w�N-��.���r5���_p΅�|Q�f�Ǡ��z����w���r��Z>�U4@�]����g}aIh�Bz�Y�L��m����{�8�"��u:D��(���m���%H�侔#)	��'�C"���ȳ��V�+t/IV��9�����)ccD;5g����B3�(�Uɝ�G펖�5�-��穉Qʥ|L��⼤/�Ҫ���.���fMƄ��q��2h�5�F�����N=��Q:�WH8�yeN!
��X�����0w(������l�~,�����w���+�[>�n����rA�P_��9�k=^ޭ�����6e����F�����r���[�
�n�SqY�����l���O���puڜ9����?둘�]�
8����?ۍ� �?[�u��D�M{���l��EG��|��g���m���ƀ�
L��q�S?�`����8˴��g#7���'Ϊr��{k�r���5���������f�w��-�>�Ĭ��z�+7����������z�7��Vl���nt�ϟ����u�kn������?�5�e���#ǘ�e�;���ȏ�1���t�ׇx�S��7�����T_���fy�j��z��ҚT��H}���V�L�����6��y�_Z�U�eU���ݟ}<oy%K������[�U�{z}����W}az}���1�_�n�Q�d���sp|��z��*���
��q����Y|�K�q��������<Z�s�χj�u??e�s���y�)���N�g��W�?�������S�k����%ט�A���'��ҐN�О��v�2�N�!���s��������q<��
_��́���J=��1��?ʟ�d�?^��������I?^M�|�j\���Y�� Ð?��Q{~P|���@��7k���Ѳ�������MV����}�_��+�hwe}�m��x����q6��^���*M~6����������">�-��Z���LC|l�T|��'����x|���xh�'>vĥ��I1��+�1>Vw;��d�����K�1�,[�[���/.7ė'QtĜ��K���rj�!�,^8>^Zs���D�n3����3����-���a˵��mlŊ@��Ɵ�����������&>��	�c,>�K
���h����@�1y�)>�*>6��|��a�w��xŻ���Ļ����*��'G�䣾��������:.
�Xx(�x��@���e�x��`U�<��~-�y�
��x/�I�ǰ�T[�����^{�|��p	����bwT��	��`���r���V<�mp3�¦�B߿z�|�2c񵭧��*������]��<���yp���� ��ծO~��Y�l���c}r������7���>�f\/��1�ϙ��B���w���߾6�ʴ���a����&�&���'�~���X*:�*9D� ����I���α%������5�52z�\4����޳~zʹÚQT��<��ml��X4\ɤ�|#$�������vra���۰A
���RrQy}���*�%��T��|��E��������V)�t����;5�'��<��S�<�H��1�ؐ�<�����|$#͝�|��������Sm�{������_c$�Vp<��[�������G&-����[�����i����(m��/`��|����%���M����6Y����ܿ�>R����#/~��0���#7�3�#�Q`Dע�����tc>��ު��_x�#�_y�rt>������>��^�;�������>�������h��G?j|��/\���g����P��[|ߧ����$)�p)�h�E�,��������+.Qg��*>:J��\H9ʔo)Sq�����Ao �?}�J�N$��m����%�H�i�q�R𽎹��\Ob�����F�ǽ��Z�����^�w.�
k�0�'��/BT}e�W^߿RZbz��z�#.Pg�{�E��g��*�ql�rZ������$g�
�oC�ea1��g8���v����E}�#����M��xί�i<�՗�b����y�������9p�Ռ�V���l0��5>���~���k�2�K�=�~�ii���߫r=X�����z\�l=�9���of����@�q�����o�,ʓ��g��7|`��q��$��	T���+�&,��ͤ�FuC#J>e�x�؈u����L�giL�mX`��	-0y=?��^@�,�|�&rg]^����S�ó����JA=�J�C��=�xg<�V��_W}��>;��']ňY���swI�j%i�g�Q]u�t��r��ytA��>�~�C�����i��Od~{)���f�f�z��O}o��}�%U�<��ޗ�~kU�K�
���y}�x㫪f�*VO������6A�Q��B��[��[�]%|�]�JG���'n����� �?33p�Φ>ۿ1��3�S�Y_�M,�g���K?�(�R]�K���z}�ҝ���i\
�և���!a�Q컦���>�=�Ceu�z�S������)��u&m�>�2�'o������?�4�}$;iR{({�	e��R��O(/���_}�pWt�#y�`1�Z����I��Ϳ�~����2n�~���?�oQ�uZ]K�K�7�=���|�b�tW�b�u�����M��l���i�i_����kی����ѭ&�n�u��Z�/�����u�og\�W���v9*�ZTg����;�
џ7ۛv��f�ތ�=��N�a���g0�.$���������1]��sgb�߶���[��������L��]3��������f&�L���m������=����n��FojS��Zg��t�jJs����IY�V�?T��zq�۽o�P�9�5��J��?���r�g"���i�DO����н�(K���.Jwe�{~�wY�jYw%;�hg��^��Ϥ�/�۷$���6�������������QE�r@u�G�Չ�@U?oH�ޤ����/ܽ���c�9�����˄�[1�)���,kh���W�
#��.��ݶ�{r�j�wy~tՖx���+����B�H*��j���JS�}�7���U�Lx��={6�i�!~��۵[e�~u�~��V���6�t���ˌ������i����jy������K�?[���/����f������Wf��Zu�?i��=���?i���Υ[�{v?��~�'fs���ڊ����$�����p���`��~����w~��x��������3���S}�D-#�:0�/7�w���U�_�e�0�3d|r�E�y5[F��Fyx��f�WC��B�ο�1y��ǺB%� m���S������4�[�����C{4�U[�԰D�k�<�,^���N�9s���s�ߚ�~���ڬΓ�|��=*��������|���OO�ޗ�3�o�p?a���j�����ѧ���|~j�da��K��ݻ-��Ef�����������?�|��͖����[�K��[���F��2��7���}ƃ�￥�Z�-q��4�$?}�0��|��������x�S���j��8%�qS�Ծ�R�wϖ��>e:��UY;-��+����Sg(e�c0��>�M;�y�M?�ۣ��{�WS,lbe�!���=U���������W���W���b~�6�����ů+�r�؛�þ�����0ǽ���?�Ǝ_D�m��]��&}O^�ؓ{z7��c���2m{����_Mj���~5a�K�k�O�-��+�k6����o1�m�<���}�,�K?i�<�����3�K�o���_��b�_:��xXl:/�����I���WnN�}E��{>vj@_�.y|r2�m-����R%�Ѣɢ!]V�d�6k�����b���ۭ��#�,�d+4��t٨��X�Ɏ�O]vL��l�duYHɖ�?w�%��:��
0�¡Á?��X��`��N�Sc0 �Bz�:X�z�`�!8cp\�����|�
���p`�a�a8�a:��7tA�M�V@��A胃��� �C0�p�CW �J��0k`za�a@�؁V�����:az��9�0��wP�p:nF�`z������ �A8C0}�c��C� ���8Ǡ��Q)�C�@�A/B?�A��л�rRz0g���5��M��	����y�a8G�}��/X
��=�=pF`:_�?�X�� t�&_0 '`1�������F���<����� ld���3����p�`��(O�1�E�`:oQ�p��B/�A?� �pC��(��q8sn%=�� �:a=�0CJ�*�=�Wz���X
���/QO�C0'`�o�_�8k`za����8p����H��0���Q^�'`�~�|��^�~hg�!8Y#�˱K������`��R?�#Jc*,Z�}X�_�?�>��0a�0�q8�����â�:���A��a F� �!���]pBŇ���>`)�A�zh�S�@T�p���
�+���(�~�A�!8G`�Ao���/��1��?�o�C0 #���YI<�a8 _�.��q�����`���A�~����#0Ǖ�/�.��R��~8`���U�҇����/X
��}��0 � �!8G����0���0�8���ć^8
}p\Ń9w�t�AXC��a#� ��8C0G����t�	�v����]��a �� ����Qr��	���aCt|�r�N��^8��8t"�O�t� ��a臞����������� ��p��(t�5���Ta:` ��0����q�.�HCJ����x0�����8�z`�`aA�7��p��M9|=��0G��0� �h)�C'���^��0C���mTŃ�*��?��R�u����`��Q��[ʇEt�@�z��� �1XT��ߢ��z�6B/�< }�%�0'�8�/�,�v��.�^�~�0�`��0�����&?��B?� �`���p�`�=��m���#�:�;�@/�>�A8��aѧ���:a=�� �#�1L�0+�%}��O:0�� ��a8#���,��W��a7�A�C0�*�1�v��E+�:�z` 6� �A8 C0cpL鳃w܇]���%]�c���ؽ}�
�c��s�5!�.��0}����B�^�>80��h#��0�a�าc�t��ܠF�N�,m&� >��n�C��K�U��т}��qҁ.8 }p��8�;�O`V�0��l��0 �������B��Ah�D>a)��z�}?����)=��a��B���>�
��DT���A�޵I~+y��!��}��;��G�kү}�ܛ��7��?K/��og�'Q.���,��J���*(�XP\=����7�;*����,�����d��Y���3���\�,���W[��C^7M:A«,�@��B>���"�Q�eӤ3Ax��=����B^�<�"r�4�x	��H�=?�<���#��@~���e����pJ{i0��q�NY�����7�ȏY�S��hTx=�W"�~C��p��K��D8YynnAaMA~��);�9zy����{�O������7��R	(�@�������tzZ�s���6���D�=%��
�ͬ�E�jz��5��I��k�B�?�=���w����;!���vaa�q�g;.	�Ծ������-��%�W����c�roj?A^f!� /A~�I>���BnǩB�W�ǿ|�?�ܥ2᝚����ѿ%���s�ϻG���z�7L���	�gwB��{�V�%�]&?���K�ߢ����Z��5&�j���u~����Z���s����j���µ������u�0��(�fo�=.���c��z��zL��ye����D��!^�7�zˇ^��_��w�K������Z�7N��į�ց+Ms�s�N�2U�^�W������+Լ��k�(��=h��]PT�=sj
Jv�,/��n�[PR�ͶwkU��?69�Y���5�����>�ݘ��#���p��D�	O����&�]"���ng>!|��=%����*(�.(Y�XS$ֿ�;jJO[� ?l��1ޏ��!%�L^ʾ��xϜe%��ꂲ�\��μ���-nwA��wuA՚��՚(߭W�<=_#�+^39Y�(�
�>գ������b�\�U�;��tr���)���
J��t��t��S� ��p_J�]��n����Ʈ�6��"�9�Vgrέ0�5kE��;�����
U
ߠ��������ĸr�<��<e���\�|T�=����{��6�3����;�<�-�W��|��z��Aʳ���P[��׉�Gzm�r#|��[w�[7�z|5��^G^'��/��/��{r�.(��=y�Kv^ŢmG��m�vw�1m�����RǷn�����zG��,��k��Տ[��!�{<u]6���x�9�S�s'���w>�~�QĀ����|�0/WHx��h�t�����< �33HO�u6�ޯk/y~`�l��ϯ�f���s������Q�֭����6�|9�ݮ����a���ۓ6�!�\�:�������=>������,�i>�>M���%޿�x�˒˻6ѷ�򾯠.���

VWԭ�[��:ŦrQٍa�
��&�h�P�?{q�:����Iu��_UwUg���ba�[7���Zix����;�w����Z�e��^�e��}:�6���I���w���r��\��q=����W���?���R�$��C�#�+<(<"<!<-<'�(���y�p��RX+\%lv{�{��G�'�����y�$}�Ba��V�J�$���

�OO�	/
�z$}�Ba��V�J�$���

�OO�	/
�^�����Z�*a��C�#�+<(<"<!<-<'�(��-�
+���U�&a��G�WxPxDxBxZxNxQ��+�
+���U�&a��G�WxPxDxBxZxNxQ��I_�PX)��6	;�=½�#����s¼>I_�PX)��6	;�=½�#����s¼��/\(��
W	����^�A��	�i�9�Ea�I_�PX)��6	;�=½�#����s¼�$}�Ba��V�J�$���

�OO�	/
�^�����Z�*a��C�#�+<(<"<!<-<'�(������Z�*a��C�#�+<(<"<!<-<'�(����/\(��
W	����^�A��	�i�9�Ea��$}�Ba��V�J�$���

�OO�	/
�>/�
+���U�&a��G�WxPxDxBxZxNxQ�7 �
+���U�&a��G�WxPxDxBxZxNxQ��I_�PX)��6	;�=½�#����s¼���p��RX+\%lv{�{��G�'�����y_�����Z�*a��C�#�+<(<"<!<-<'�(��'�
+���U�&a��G�WxPxDxBxZxNxQ��%I_�PX)��6	;�=½�%�3��}-���kݸe���/�X�uˢŋ�}T��߇���m����v���m�Z��7,�غm���Z|���4ڴ��u[�m��n���f��v=�cC�֖-������o�S��6�߶������s��-�ÿ���MHQ�ҸοζhC�ڦ�u�7�mnl������k7t����_���
    typename T36>
class ValueArray36 {
 public:
  ValueArray36(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5),
      v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12),
      v13_(v13), v14_(v14), v15_(v15), v16_(v16), v17_(v17), v18_(v18),
      v19_(v19), v20_(v20), v21_(v21), v22_(v22), v23_(v23), v24_(v24),
      v25_(v25), v26_(v26), v27_(v27), v28_(v28), v29_(v29), v30_(v30),
      v31_(v31), v32_(v32), v33_(v33), v34_(v34), v35_(v35), v36_(v36) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray36& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37>
class ValueArray37 {
 public:
  ValueArray37(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37) : v1_(v1), v2_(v2), v3_(v3), v4_(v4),
      v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10), v11_(v11),
      v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16), v17_(v17),
      v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22), v23_(v23),
      v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28), v29_(v29),
      v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34), v35_(v35),
      v36_(v36), v37_(v37) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray37& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38>
class ValueArray38 {
 public:
  ValueArray38(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38) : v1_(v1), v2_(v2), v3_(v3),
      v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10),
      v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16),
      v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22),
      v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28),
      v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34),
      v35_(v35), v36_(v36), v37_(v37), v38_(v38) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray38& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39>
class ValueArray39 {
 public:
  ValueArray39(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39) : v1_(v1), v2_(v2),
      v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9), v10_(v10),
      v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15), v16_(v16),
      v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21), v22_(v22),
      v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27), v28_(v28),
      v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33), v34_(v34),
      v35_(v35), v36_(v36), v37_(v37), v38_(v38), v39_(v39) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray39& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40>
class ValueArray40 {
 public:
  ValueArray40(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40) : v1_(v1),
      v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7), v8_(v8), v9_(v9),
      v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14), v15_(v15),
      v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20), v21_(v21),
      v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26), v27_(v27),
      v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32), v33_(v33),
      v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38), v39_(v39),
      v40_(v40) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_, v40_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray40& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
  const T40 v40_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41>
class ValueArray41 {
 public:
  ValueArray41(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40,
      T41 v41) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7),
      v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14),
      v15_(v15), v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20),
      v21_(v21), v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26),
      v27_(v27), v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32),
      v33_(v33), v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38),
      v39_(v39), v40_(v40), v41_(v41) {}

  template <typename T>
  operator ParamGenerator<T>() const {
    const T array[] = {v1_, v2_, v3_, v4_, v5_, v6_, v7_, v8_, v9_, v10_, v11_,
        v12_, v13_, v14_, v15_, v16_, v17_, v18_, v19_, v20_, v21_, v22_, v23_,
        v24_, v25_, v26_, v27_, v28_, v29_, v30_, v31_, v32_, v33_, v34_, v35_,
        v36_, v37_, v38_, v39_, v40_, v41_};
    return ValuesIn(array);
  }

 private:
  // No implementation - assignment is unsupported.
  void operator=(const ValueArray41& other);

  const T1 v1_;
  const T2 v2_;
  const T3 v3_;
  const T4 v4_;
  const T5 v5_;
  const T6 v6_;
  const T7 v7_;
  const T8 v8_;
  const T9 v9_;
  const T10 v10_;
  const T11 v11_;
  const T12 v12_;
  const T13 v13_;
  const T14 v14_;
  const T15 v15_;
  const T16 v16_;
  const T17 v17_;
  const T18 v18_;
  const T19 v19_;
  const T20 v20_;
  const T21 v21_;
  const T22 v22_;
  const T23 v23_;
  const T24 v24_;
  const T25 v25_;
  const T26 v26_;
  const T27 v27_;
  const T28 v28_;
  const T29 v29_;
  const T30 v30_;
  const T31 v31_;
  const T32 v32_;
  const T33 v33_;
  const T34 v34_;
  const T35 v35_;
  const T36 v36_;
  const T37 v37_;
  const T38 v38_;
  const T39 v39_;
  const T40 v40_;
  const T41 v41_;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33, typename T34, typename T35,
    typename T36, typename T37, typename T38, typename T39, typename T40,
    typename T41, typename T42>
class ValueArray42 {
 public:
  ValueArray42(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
      T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
      T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
      T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31, T32 v32, T33 v33,
      T34 v34, T35 v35, T36 v36, T37 v37, T38 v38, T39 v39, T40 v40, T41 v41,
      T42 v42) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), v5_(v5), v6_(v6), v7_(v7),
      v8_(v8), v9_(v9), v10_(v10), v11_(v11), v12_(v12), v13_(v13), v14_(v14),
      v15_(v15), v16_(v16), v17_(v17), v18_(v18), v19_(v19), v20_(v20),
      v21_(v21), v22_(v22), v23_(v23), v24_(v24), v25_(v25), v26_(v26),
      v27_(v27), v28_(v28), v29_(v29), v30_(v30), v31_(v31), v32_(v32),
      v33_(v33), v34_(v34), v35_(v35), v36_(v36), v37_(v37), v38_(v38),
      v3��K5*���"~{����ۃ�&�͛�=�f�ִ�=���{�b0�l�TC�C���o0c��[�����d�wi�K��u��`�V�LD�^"��2@ۘqM���ȮF���kHOT�%U��ڌ�Ӧ���ڊ������;Ɨr/X�r��t�"ifÿ���
�������Q���'�s���5���[���1#�K�&�Ͻ��~ѷ2敲��ൠ����z9�-tu��7�Sh�-��I�a�F�>�14�
/�O���8H�kj��� ����:�i;r�,ܦLx��EO��	��3
�Kagv>�;�A��7����YЇ�?� <�o��f T_���g�
�9���n���>���ȝz�C/�P.!E�6k�Xݕb�����"��B���o� 8�9q,�e�w���o#;�@?J:ï#�d�ֶ���w�1�I����2V�Ģ<�2�ߠ ���vu0��@��&t�`�UzU���g�
�>�WY��Qw���$�^��-�����GD+�F��� |�2V�ů�@����@�7-<�(Qi�{�ocu��i��P�C���&��WȬ�s�_Z�� ��u�����-N����KS-Uʃ�Ҷ��VݳʌWX����c�B2q���<lLcg���+���*�T�������.�u
�U��n3���rwM���y0w�WI���x��+oa����@3����o�x�5���ܻ����K��᳙k�Y�04dlo���ؗڋ=��nj�+]�N�43�'�����d��+��w/ito�Ini�D���8�mP|(hr�+|��n��G��4�@;��=������
u0�[�!�0��J�U_�wB��ǣئ��Y����k�����k�7�
���I�j'���6O���+��;|iK��KV<���� �v P<L��P�g7B��Y���/^�g�r�E���ȉި	CF0�}�U;{	�Ż9�|�%�Ώ(7��t�)��q*�9x���8i�x~,�?4g؏W�tY�8�mnK|���'Ū�~���@;4tR��4����L��M���[ԩ���� l�s��$����|�uW��
�ת��C�
�B#��w��d�Jb��m���W��װ����{��5��b�]���{��t6A�sd(�3��L��l�%���|1peth��� s�8�+�$nA�B��?�Wr"&p�a���$�t�q�Xm�KJ��W�G���~��KT+�^����
�{����8�Sl�A�M���h�� o|V����5�7)@�W��|]��L�m��S�V�*���=�w4��+����r�W�f��|���Q�v�a�i|���F�g٫��'5���|�yD(ne7cZϞ,��r|�s���۠_}��X��"ξq���hɬ9��9ڣs�2����~�*���^�r�䛦c���܃ػ��|���
μ4(BW���f�B�3��'����9ri�Si��G+XNǒ������ߨ<�\��2P���V������Ը�΄�EV��z�ӟ�%�g��ȩ�g���k�A�,��#�u_f�V8}E����d��fۡ�+�v�Bi�>;�ط��:a<�G�:fMV��s�r��H���{l��y����qP���"2M�>Ŭ�,��o�S���/����2�������g�P.���|6!jP�{3tz[@pf�	P�N죛跿�X������a�w���sz����B/���&���U�[Z�`�'�zܘ�'�JTU�﯆Yk��T�.�o���=���A�C�:����J�e�/A��bx�2�/��
�g������7O��7_I�Ǹ�6_�]\�d���Xbq�q�X�S���߷��=���G�E3#>�^�}�������w���/���[��wU���kt+�q���O�3����2ԟn|��U} ��Tٟ/������ƶۿ�������̥ްy���mO��;�b�w3���_�9�⃙��L���Ey6S��J�c���ɨ%�C�	��u����I/!7��I4���=��"!ʰ�*��C��7�O�g\�'��_���]鄽��.u�k�awJ�u��]�?��ũ��ᏹ�Ņ�9}�z��N�t��7�Jޝ�%���᭍��ێþ���=���P�>�)�<�r�~��X��~q�9ݝrV/�,Y2|�/vߌ�9��<9&yϲ?Q�	���ݸ����^ ^��G�E�9�Rt�lF�taW
�����})�_N����Qt�:������3n����n�hN��?�A���X=W��h��滸��D�xT<K0D��%���fȘ�uH>���vt�*w>�+i#��p��C��u�8v�m��%�� ���r����h��~2n3d������՜w��꾊u�7��e�fu29��'��|����Y��ѽ.%���v�'p�IC���}���L>����ݤW:�񦚦��=��֬M͗�{�䭏a�"ɧ��.�h��̕.Y�/�3��C��/5���>Z���e�y�Chc<�ϴE5�k�'4ưxx��!e���~>u�+�'ɟ���N,�r�~���e�Cx3��C���\<�{��;�)E���q�Ѣ����^��h��R}}#�����eZ��ڌ������e��j����л.�w�������������ۣ�ť�����)��&�'�+I�~�N��L��WnV��74����''*�=L�do8Ȳ˭�5Ky�av�qm���g���,|���=�N_�7��.�/	^iV�U<�3�U��f����ۼ�]Y܃��dm�v6V� �]ąvO��������NMo�y�L���xqĄ�p��ή	��r@�J7F;|W��n�����%x�s�o܏�H`{Ey/˙4X�l�[��]`���ǘ�
C��a���6�!�����U�{��*��6|��.,S��7�xŸY�<�7!� b�|�i5��#+����
�����e��v��!��0��ϣ���x�u1�·Ҝ0�mj%/�3P���i��_�]���6߉�c�̊���4�Ű��a��n+O5�Ph�o�r�#�?�j��i2�,����G�߻�1�|�bnd'���3Ӌ���K
t��!C�
bi.c������H/)�\Q�����ṡn��t8p�K+�ԵX�Q��ln%���4_�M�G��-i�WH��%m(}~�}v����rx������/rG����J�K�Ǜ*���"3ڣ������q����
��O���A%0IP�y�~�		�
����1�C�,�ʹe��
���
\�������P	�H^�+����d	�J��*���*uФ.Ah���2**`BV��
�K�᜼a�z�,4�Eu���P��2SQ���E.���p��T�/[�ț�2�T}�Ea.��˴�PB��U��r�
������J�Bh`�˼����;H�[1xө�yH��r�`�;0�sm�S���r�s�y��ҍu�>/q1��af��%��Ɨr�(ȗЏ���
�T�+qQ5�0����I��2r�%[V�9�E�����a0��K�Ԝ���\Ԝ|$.�W5CHx��EwA��Ұ�핇��\��xJ�*敄���f�ka1�Wi%iZ�G�0~����܊9HQ�_�_I�"U���y��<V+Ys��3����b�B���z�׹e%ԭ��G��3~�tbEG��0X���"W�"���6�n�:?���\�ܼ���\��@M�:.!IW��.b�k(�%��!m8˰�<�[)��&��0?O��LwGQB~)��^��-��uŕeIIÓ�:G��zD	!��CC�aA�rx9<�D�!G�#CȤ 2)�L"�CHkb���:�U��Wk��V���Pw�q�dGR�`VqRB�n�#;aĐD����
&H�ӳuE�f%������J�uİ��	>	=�&Bm�����F@��2OI�9h�����v��
u�W|�͛�����ȏ��c�������Ƌ�>�����X�,X�;���t��?��h�eم�a����P��2i��/��.0�~���������������_��������>����?�~����������������������짼<����]Z��SxN��w�>>�]z�\�))�]��˫�,���g�n��*�n��Kuw,��I����[������,����;��b�V�RWMT{���%o��
�Z�[���h�-
55�03�G7;��h���eXM��F>qn͘v͈@>�f�3yC7t��8��>dR�Q���L�L*�qT�wff���-�h�TCd6�\VY�T0������yVD��l.%��raӃ�
��yA��D.��ƀ9F�y��أ;<�r�l��4
���4���̘�4fed�f�-k`B�[z���3������QF�I�L�������lc��Fa�3�l
�Q�mF����A�p^��2�.eZ�Ȋ6�)�+#*UвF�a��Lq�Ɣ�Q�]��w��݉��7k�-df��T�ꙙ�̏�����v�d��%���:i���@�
 k��
�ff�Q%ffF�v㠳V�t��	���à!Wt��YcxsM�-�z>�3��ό�a��KF�o!�(K�,4���p���C��f�*Äy_fM�>���
��C��-hl�������*3���
`�m��{��(s ٕ��gZ�!gfƳY59B1��&;3��?8�`R�7;j*-k4�Y�
���2��IZ瘜E���v��T���ܮ�opײ���b{��m��Q��𝹄/����r�íT*!�;!�Ē_��Z���m��^Sw�h�<����$oC> 9�J���؝%��N;�l�:�k:$��FH��`��6xPI��`����M��4]v�� �i���LD�u���ŘD� �`�(/�����^���d�����]"ujJ�}ޞO���%>�'���]�A�����gkuά����ǭ���ь�S�U��a��s��I���`��%���mP��۞�&��f�/`�����.?��6�Nk��e�6O�K_��|�tlѲ��}�c�a4_�/t���.��]w^�۶��%O(;�s
sK��lŏ��E�+[t�"J�����+lwi�	���q�:-υ(��"��L��Pۦ쯈�|mj�.BĔ��?�ݜZ(�/�ց��|A,a�b��Y� ��ߌ�R��؊ؗ!&�/	���O�vO��lXD"�jqoS
m�y���5	�P=7DSʇ.)��Y�㲄`um��,O���4�m4��<W��",�00�YZ�{K�mi�l(z�XR�5��ǰ�P�{B�0�\ơ��#;d�a���yO:�[����1���[�S��)x��Ǿ��'B��,%�5>t�B,Sí亘�u���^��1ԋmQ�"#fY��X�^�����lq��*(�*)0�NC�m(��:c\1=M9��m���2	�g��z�x���A<'{^6��<nMapSS�)�d�,1��ZQ(鐴O���0�1wE/���� d�-�������U�"X��h�\�{��X���I�������ӛ�5����bV�0L��x�wJ�+�K-�NV!���N���TXN/���Q��eTÔ�\���-�.̄�ǂ�T�z�fB�z���~�u�HzV�	��n��4�OrE%��R�(��9��E;l�w�t@$boj�h?�C��#a�}��B,T��ǰ���0�~�=����*)���-	A.�^�qNxX������^,�n�*��%���?�9<��9b&����y0�|G�/�>m���U��Z�H̟rd*��	��	�-R4kaP+�&�3L���E\��@�������9�_��+���щ�-K4ч�<�肌5�v��Ф�K�O�,�%,�8�}�׉i��I�IO�a���j�p�bɚl;0�*��]@^ �]���B�1~ᧀk���������$R�N�3�1���*���.!)�
ة ��e�m��q��k��&�Zf�i{A
;����E �E�䩖H۾�I�:�]oR����Tq��=��Li���<$d(�+mn���yL���ì��]��7K�z���a�	5���~ �
"!e��� �RQ�"/�d'1��~{�	%��Cj��D��

�����C����:���"CdĢ�Q��BU2Q/,<�T�I���C�İ��tC��9�UG@�EQ����<�kB�b� #��i�S���@0����(,:�"��=o�(��^(U9��I���Zt�B��)���(Kr(�_�zC��.�E:^* eX�Buԍ F�!_
G���cN(AG]@||'!a�� �/�\@UB�S�V.C�a�����G`B�u��ң�.�f&�"�����(�|��ʀ�0�]���h1p+�q <�+���3�+^\j�Y4$ܚ����x��%6G������dJ
xZ��r�R$G	F2�#��b�Aŉ�f?g[���a"h�Ip8r�%���疅e/�[�
�0$�J�3�5���%�[�9p(O�����	dO{
��1�ܑG)8��Sh|�����㊀��n3r��ỵ�c�'j��?�^�3P���P��X-'I� ����N0X$��m�@rBh�I�뀡�B.yD��j�AvK��]�.��0����{p��bz`5|Ȯt�:1��L�c�6�X��5A����}��4�$����y�$�^�c���P�+@����C9/��LEp�8�W���q��P
s�UpB�C�O·��#��Q�`�H����8`�������s��C�2X�D(ș�~@L͐�NDD.!��
q�>?	��=����Pky�f����%s���M�/Tnf��K�R� )�=J��X\͝Z��rY��H��a0͔�*\�g��8���Ъ�L|`V��p֡�lS�Cf{58�y2�x$�eӤ`��0����HS��1��y

 �P��<r�ω^j��&�����7�<���r�W	�
�G,r�ߩ�BEK,�+���J��U	���I�>�e[��y��� �xR$Qr�`9؞P�`�><�x����U��EBՙ�X���O1m��P��E�!��R�(��Rm����2
9����!�`ǸFf�\�/�����V�cT=�'ʼ�v��KV6zAȑk�6�����B<�KAZH�U�ɛ��
 -닎�P��SMp/!�H�ҩMO�U�Z�f'�c5�X�	�N`9@P~b�&���JI�CX(�\�%!u��)���Wt�4�9h9����0G��4mYA�M($D.d�b��Gs��ߡd��+@C�t�$!����|ل�jRƥ�s<7M,x--����J$�:Ռ�F�NQs*b]��C�&[��28���� \�O^#]�v����@ٴ2G�S��) 0B���:�XM���x!9��Cu�R���[:���.S=m���3�`XJB�2J���(2���ӅP�#߃�qt�b�"
B�����<��|X�$�?�"!�,���� 9�H_��Vl�2OL���TG
KK_�U� џK�Q���?�}�`q�4qM!�(�KKe�,=�����@�!|��X�@��o��p�v�a��]Œ%(���e uJ���2	�(:J�+E������kR��,� x�;��_j_��@������T�$-ّ&�%���aCP!���$��=����h�7U���A'q+R��^%�Tϙ��}����-��|�m� ��"�B�D�^�X��W����&��*�ڔ\D��}N�N��ͭ���Ţ�b��M�x^��V��l��q�,4��T�R n� (`ω�E&����0O���)�D���DH8�����~����9�谲�̿��y��a�(��*)gOy;]��Kz��9��x
!X ڍ�J��(V.d��"���F�4"�}��٢Zc�Cj�N֙��EĘG����z�_W�=���T�(f	ײ15Q(;0d������Y�-���2L�	�6e�1���� ��'�=�b�!��0C�q�0�@E	
�%-A�(qs���!\�"�&�!D�˫z�O«tM�O���"�k�u�N_g�XD���φ#��ɅX�9[hٔ�^��jN+:�^G���O��e�9)�J#�*�T@��X���K��ԡ��\�P�褱'W���)?N,��Y��Ŕ\���Ar�)o����)�]�=�Y0���3�N`�,<q�j �.|�vQe�Q_��j90q�1�,�X���X�� �s�T�%PC�mIG��С�j����bE�#[�PR��dH�(Jc =�?A�kc��
iE�lQ�w���3b�Sg�IQ�.[Q��a�sF������ҋ�G�F�� �.ຜ9�T�-�q�x
��N��b�P���h,/v9t�(u���>
�"��CO�cc̀��� *��ВZ��ԩf�U��ʏR�n�o[���]&A���#�O|�<�-%��a�Ҳ[ak|��!��6�A@)J:��쮋1[05�<���e��Q悚e@Z��q���\L�G����V(| +�R��z{U���$]�����,I��g��r�eO����4��+�wG�����I��' m=	�C0*R/ThѨo��:�+�;���9�ޛ߃=���-@�Hka.���0w"�k�VVw`ni��Drq��G�)�"�Bޫ�sD�N�
�<I�fU�����Z[YS��_�-r2X��y����"�����"�:{�W'�X!fW�#I��u����I��ql7p	���)�����s2�q_	�e���'�����h�����y�'lp���S��V�$�VuR0�MD;�OÙ��OAn�i���{�8MR+��BJ���iĸ F������ī��"�@8nj��Aچ����3������q�i�+!!��1� �V��c,��	�%o�ז G�J��eě|�o*�8������.z�^qii�AQ��0[�I�0s`���}��ԈV�E/��1�����9�������zP��{ҍ�6�^�_Z'EV�2��
�[ڣIѴ�H��ݏ�mD���B'bN���i2�2US)E��S!j��6%�B!�uZ.p]�����IE���j')�p�S������BZJ'�p|��}:{N�$PX~ŧ���.E��5'}L��Ӷ�v)g�+�C貝,R��Ӏ�;��T$���%��M_E���u\��G�rɐ��6�D�a�] .m�s��!�U�4o��Q�L{��B�dqH�Z����3�ӈ8��1D��.T��h�L���
�9��S��W���	�J��`�h7�
��d���E`sR\��0ըI�bg
� �;�a��!�K!�B �z�piͶ��;'�^��O��i�T�0]�؈���(�Q�]�j���.�*��dΙ���-"T	MOKKo�r��e	%��B�je�X���K.U���kDdD�k�~ٱ��E�҅�S���#. Tܧ�4���
������'�1)�>E�d4dȑ�<�B9��T��o��'3��'(���X�9|��
%CR/��8 ,��a$��dH���pˇ��`�	}�k.�P4�q���w�=�t����>���B�H������D��5]Z�]�ʵ��D��lJ�V��$�R�S�L��c��
j����a�k����J`3��K���.�9�δ�1�n[��-R���m������M���mIM�|.-6��ȣ݄�i��"�2G���>�ΰ���k�.�d��19��JR��3`D�c�,��s:&��E���֪�yH��K���f 
5����c������FV��Y�I'�$ϩ&F�#][���4@�%�F����^'�h�zڱ��d6�X#���͐�`О]�:z�pÞ\@79(WG���u���^���Ͷ�����J�(���
I�D��T��`��al�qA��+�a�dh�+��Iw|ڦ���d�2�D�t�RI��zIB��������YLK�K��>�l ?�����%NGE.E,��+u���. ��Z�X�%K�x`yT��fR�b�pŮ��P�-KquGy���u�\;��6���۴��t>���y�L���B��`��O�Q����@��:;�K*�
����I*01��vit��UP�L�K���z]ȔQ<,E7��ED��MڥD�2AU���&({M�'1�>u�-5�\_�ܵ�/����۲�Ꮣ�F�5r=?��?.=r�\�<v6<x"� 8;7�W)�AI[�f�Kۼ��&3&�<MP�yG���٘���(׮%�%:��M+�9�<�\x��Q+U0.�c;��n<I�oi��d�S7��UyS�؆����V6e�e[vh�&�	!�F��ћ�c@)0o<
�@�F�q���/��j�v��	u�sTˢ�Bw�ӛ��Cq'J�Ɖ�E�.�,�����Ԟ'��X'��}�I�-�����}��@Ҿ��p�(��à�٣U1��-B�ҳ���cu|HfJ���0 �x/$[B�dROq+�C��S.�;�<;�q�k��-k9h�K2����WCr���&$-�j0eJ��
[:��C����^�.�V�vi�4P:�&���BHx�RpM���酌0�I�:!��'�����mÄh ��je�z}��,�V:T�c	�Ȉ�h�ۮn��0
�q�-`F�Mf�\+Ğ�$z�Ts�E��G�kM�Ǹ���s^�q�@\�����eA4��s�_V�z_<�����-h9�Nx[��� �B���w��u>FȠK]�*�_�:����K��|8KC�d�\�A����	(���'������A\UI��h8�?T�\��]�G�R�5{^Cޥp�����q'��y=�-h��A�C�3�5���)s�L��OjK(�	`�WhE^�K07-�i�&�M0����N�Rz��5��g��zx���!��`m.-�g�6C (�K:j �#�L��:�
��<o#�@�u|���}#Zf6v3 ߖz����͠��|�٧��]���L�_��V��Ά�vZ:;��h}�d����#�L�֩�mn$�]Z��lt�F�>�M+jE�_�ܒt=/u�#=�Ng�mtEE<l;���"��d�M��h�X'Ћ��qZ"�e\H@ ��>�L��	e��\K���RꗧP ?о��}��[�0��	���q��F��j�w[�$�s��n����r�CPzq�θ'�5z]A����ݴ,�Чu#��6-r��J@���2:StDYNߓV�H��6��Q����aF��q��� �)C���~!�7��g�;�Bm(��t����%��C��a3v~���Dw!)��^��lԞ��W�������MҖU�'�<���������K(r��Ю�&�؝6�0A����2�5����IZSF�~@;����y�yQ-_�6�ȡ���Jk�L��v'D8�d�,z�*�+i��9��vn�����g����?M�X���:���@D쑢�gզ��>��SڢV�@VK���t����g�g�i�=���
�i�Jk�M��E�x�V��]�z��4��ǔ�E�)b'��m0mM�9� �?���5G��F�-����!"��l-�wk�t�hS7�H���@Ea)���dE	NQ��L+�I[+�����C�)�Ŝ��h	J�0���
�pnM�&�g1��$�0K_����u"z�0����՘��ɂ�=�e	O��&�R%��Q�ށS����z(�-�N$��F��ikC��1bim�\��y��ȧ4T��?:�;��UuO���G���>N�i�)�uZѡ͕�^c�ҋ�$�M���U���v������h`�����g��R,�B���L�;����j�i�d�(���Q.ғ��Dp���<��٦�n;�����@Gܰ�6a��!�1%�ԣ=" ���i��B��~	|��z7�j/��T�ƴ��r�L�$
���ԭ)��'=�ʴ9�۲���4�מ$���3u�b�{v�AvU�ʶ�:��c�l/�w�
��.�Q�^ӑS�q`����#<�V�.��OB��K��jR�iȺv����<w��N�F�V �:+>PK-ukZZ�E/�k[_&#}��9��٥ܾ�+�O=%�R�ϡ3Y�[��.2����l��r���I�+B,��(�%��h�&H�t���
A'���&>�hц/T��T��|���\ey�^Eb-��IQeMH�N�`��i�\�}))�0�տ3��~R�
�6Xp�8���X��.2���"fsՎi�v�h��XNB�w�T�z)�-�n��x	���ꊔ��j��ħ1?��WV�p��t4��V��B�����I�K6��m�f3��o��}�N��lz�YqX��e#���k����%� "3����AHPL�G�����d�f^���G@�%l�䋹�wJ7�x&��C(C�.�b��Dx'��K.��~궚>a�C;�αs�;����?��s�;�αs����̿\��������4gWG�+�����Z�poc{�j��a�ߞ�7���U7i�Z�Zh��W3k�ܰ/�C����r�����y�2ʫ��|�s�/������c�R^Fxf�h����w����=Ͽ���|���ifd;c���{>��0>��fp�/]�<�F�#��҅�2�^�t����ۗg�Y�n��l�G��WG�Ā�۵K�m
V� �cu^\{c�^�r��g�ܮnlf?�����Kl�d�����,��="�y?��ؗ���f�,�R^u������}j�d�Oi��.��۰��b{[��Vs{!�rI:}��t!�z>�Y� K�����}\i��.��.(K��]�]��|o5��p)uW/Q�6�����K�m����5�7���6�?c���sJ�`�������<s[��^ȞU���򳴥�+��>n#��^{�ޫ�(n/O7�7ϋ�����%K�~�t�qc��5L�����e��M;�]�2*��i�H�����˅lV��g��v�8�TJ�a�:_���&v�zQv~���|����v<'�ݸ񂲴�T��l/�Rq��q�`�.one�J�l�绷ݸ�Di�������ko��m�y���b�U��G#�Ë��Ջ���qՍ9��嗶�F�c7`��E�w�o,���U/^���m�Q�s���ji���V핶�K��*/�TGs��Z�_���t.Ia�o#K�m��/�Vl�S7��E��ה�~��b�K˨�y�^0V��]0C��m;Q���KuÚM�z���}��+����1'7\C)U��u��_t|t����s�[����e��W���?7[���j��T7��m������E�M��7��[ǹ V܈Ӷ�ѫ�ϱ\�T���^����V�rI����TG�K�Rr:�㶙K�s��y1��v|����6}�������K�9�j�"s�]����ׄ�/4�ۜ��g���҅�˶��6d�R�r)�}[v�z��}9���K��nsm�Ʒ�|�k/�(�Ջ�u��ט+���8�u���f�Җc�n��;UK��.K�^*]���v����G�_����땳�n�?����K҇��9�ۗ�z�e��$խsd����W/n=���K���n���l|�-��^`���{����Ra�%a�m��-�}�qOu��~���v��c��9v��c��9.�([��
M;3sypk����˃+�^�\)y]�̐�F,�C^��FyXM�����P.vg(?��
s9���h��8\ڲ5:��A�6���|�G*/�Ϩ܏�]�x�L`y�T�\���3m
���Uy�2\S�=��@��#�W�U墑/�����#�X4�C�+[c>� �ֈ���ЂY֘ݡ�,ῃ�St����i-�*��JVI������5����3PB_��V������Z?�Uu0/\2%J���漠~�J���u4��i�l^�dF\*���>�
��Ų�.�1��JE�jSk�s�A��:3^rXQi؏�s��T���E۱AJ��ڠ�+���Tx \C�3��О,�@��U��]�D������*���m˙{q�c���b���ߪ�GX}pC���Ѻ7��h��qp;Vr��9v��c{�b�c������׿s�/�:X���.��!���"*�a�q�W���_1�E�PD�#-�,���Ȅ, �1C_S{cSrp�
�O���3�/�����gϽU��nЇ~�칯�>���?@9�3_={��+p�ٳ�}�k��cЗA�9}��_�}�wC�W@�����Ϟ{��?9{�z�}�ހv@o}�!�wΠt��A?��9f�L��,�w�A�^@�����_=��K�g:gϵ�N/�g���o����-�y�ς~t�4�AH�{g�]}5�9�q]A;�m����e��ρ���o���/�>��*�m���r�/�����Lb<k����?h�����i�#�A�]���C�3�W�)ڃ�A?z��g:]}����܇����pt�e�g�����F�w~���YЫ��~�~�eЯ�{���0ЗA���`���@��Y���w��h����ym���-(���A?���|��+g�}���v@��	|}�_��oE��
�sk�O��)�]�s�Dm���Nt�?�L??G"���=���=u9�/�ܗQ�ٽ���6�������\�7�Ǘ[pi�঺qמ��F��Q�AM�}����p^�k����yಟޅo�J��^j������=t埛�2����J��ۯ8�~���8t~���rn��oЅ[��ߓO(�v�)��ߣ$y� �ӭZ��*�\��@�>���F��y��Ϟ�e�p��KW��
� �?|۽��f��~�G�0�$[/
m|m܂6nA�L>��ww݃��ƽ�g��݇k�<�q�Ý�q*Gqߵ��F}����uq*�Շr	�����8����7rMr��ۍ����+�y������k/���w]v���[C?��K�jyS{p�@N���܍x���=GrG��2������13�O�C����}d�s��c���(����jז����w�o�έ{&f&?p����q��7Ξ��&��� ���P����=�羆玖���cf���8���4�{	�}{DN�1"����ܑ���~}�|M
���?��T�}�~���y�R-��Ч���~��o���[�|���J���G?Qz��У�73��#ٝ�?�ȣ��ԡ���q?T�����=Vz�'}��g��A��ާ�<V)��㟸��G*����?��#ó��+�<Ra��������nT~��M�1�'k%���裺O�?���o��C�<�?���J?�ZV��u���
�z4>h-�7`�?cD�KQ�C4�P70��Ka���LH�a�� j6Z?F���߇h�֯�����τF�B��0>��
���B����0�OF?��������0�Og�����3�a6.���2��7�z4:M?C0*��]?��重��hNꇅ�T�j�q@�߄���8#
-Ì�~ �Scx�c`��	@��L0�)F�F�p�rf13C�o�4#V���e@̏�����H�����o��o R�v fC����կ 
(X�-���	A($�C�"*��EEDQ�*�e*�Tp��RP��"T�R��o���IN6�}������{��{C���=���^{���t�
��j���5�c����[�Y���x����q񯖍U�K?����\/�O�{MC�_-��/�������>��$��K
��y��ɟ��熟~s�7����S�7~��,��o�^�����+ë��k�{~K����օy~����������G��~���)�>��aϕE[�͘8e��M{���d�Ƅ^7l>0y����_�b�G�u�}���zČ���-�>=����MR�/��}Zn{|��듊�{`��a�1Վ�߻=���b3N������.Og��F���;�#uN�?y��=>r��޿~<nԀ޿i�S#z�ϙݳ���7����;�wY����	[���Ua˪��W~���Cz��\�쒝7�׽���=�;f�uk��ظ�{�˛b_;9$���O����>��{c��&���<&���}��������[3h��'��\����)�xoYuǗb�yl^m/Ý��+�\朢����j�+KW��%kˣo�m��������6��{��l�p��k�MKﾷǆ�@���N��V5{��ǌ��������mk���G�U[�ͮ�����v�^kl�?�>�.B�	�1-Z�/Aü�|x���)������1��w���|�D��!���?��>^!���Y!���G������>~"Ry"�E��F�ä����"���z��<oG�?S"�����!ߧ"�?=B:��l�L�|�#����`�Ю}�!����"���1���|
�+�_
2J�c����ԡ�3������8���N�/,�:v\~6{�����ұ9yc������p)�cKJ�K��'eM5�8��9㳝%H��
���9�(;c�PX�]��Wl��e;!��YHfd�3N1�H�V��%�D32X�qyYW��I H�0�U0ilI�8�U��(;>�e<	�������A�2�ЧOFII�؂��̛�]��5v*��+�g�b`V'�/��YHB�).�d�h=/X)���8(
�W�t9"Ibp9u@�!0o�$�&�)cR��ǹr��2H�b
E �������&+��h�337�/{�/,,bO�ˉ!2k��S��p*#�$��%B(Ԣga����@��Y��y�Y�%��yE�v��ޅ9�_^�Y;//Hk�$����W�Q2elQQv�'��PX�19�8$�Iy"-";�TP������L'ڭ��dk�Z4�sAa�8h��� h��g!�1�f:�&��j��W2�p��d�'�V�IȊ�j��ٺ�N��qlVƔ<gn��,�*K����`�Λ�P������e���-?o\P�h'&{����,�F�=9�:��,,?��k�0��lh��B=����'u�3'a��� )2Uh��
r�Cd"i;��ةO,�,#�
�8EB�����փ� &Ġlg.؍\Pxa`������
��P�hs1����dƳĨT��ٺ%�œCI��LlY������Z��2RB=�ľ/Ok<T�Z]��S9�AU�o�� \;aW���6+h��\�J�%�#s��D{=h�}������A��Hgv~���w��r؟��Dq6k�X�y��3�'*`F�N��\�6�J�:�S���[�)ZK�V�y[I�m���(Ci�a�onK2LKퟒq�m����;�Ow�^�>�ℰ;n�+p6"��Ϡ{��ޅ��!��K1V��W�P����t���
��՗�?�՗�����6ǫ|��|���k��^��&?�qñp����$�f��	���Ot�z��x�$�s\�G9�.�c9>F��9�+��8^*�9^&��ż����/�8�L�����ǫ��������~�7��7	x�f��$���p�2���:�[���� �'	xǓ|)�o�^�����g8^$�s�L�?�x������3Ǘ
x#�W
x׫�^���&ʟ������
��_&��_+���p��|��|6�UW8�$��9n8���q��f�z�/xx���q<A��p<I��q\�μI�^�1~�+�p�T���x���x��gp|���s|���8�R�gr�Z���&�8^/��s�A���x������i:!�G<�Y�Kyx������~�'	�	�'x����.�7q<W���x��;8^&�#8^.�9�X����R���J��ï�g9�M���x��/�x����*��x}��&�pR�w���/9'�u<�xo�����O�S<�,�&�z�9>F�-e���&�T�e�\�������R��e^��_+�Sy�j_���	��������1Ǜ��ㆿ�q�M�����-^�˟ ���I�7�eo�x��w���]�M���x��
x�N�����n��b��_&�<�J/��<���&�S9^/��8� �or�I�7p�E�7q���o�Y��8n�?9/�-O��Rn\�x�������R�w���	�@��	�0��xO�����
x�W
�T�����&�>��	��o�/8�
�����7�
�ws�,�q<N�;L��.��9� �q<Y����!��G9>F��x��gr�T��r�\��q�B����R�������k|ǫ�0�׻�7�����ë��)n��Z��q�����8�q����x��O�x������>��O��9>F��r<W���x�����2����5��J^�e�+�R�U�Z����	�9��x�i���o��9�"�f7���B�������[�������I�Ǔ�U����.��<�n9��������x+��	x�'\����6�����/ษ5��q>���>��I^��\�r�T��9^.��8�L�_��Z�������&Mn^��M�����L8�F���o��&��kr��8.�
��
4��7�B�xj,PG�q�ѕT}it!+�ޏ4���D�F]�@ѻ�FW!PF�����"�7"�.X`ѕH��H'���u$�>��2�~it�� �.B�L�B��e�~itM瑞����'�)�/!��.F�R��	H_F�=�n�?я#ݝ�'��/'��~ �+���#G�}�W�D߁�U�?��@�j������'�*��%������;#݃�?�t����O����'�8�7�DF�'�O�~���?ѻ����'z�7�D�@�f��H��DW"}�O�'H���'�}�o%��~�^�?�K��'�O�B�o#��~�ۉ��T�H'�D?�t"�Ot1�w�DO@�N��qH�&��~黈�A�_�?� }7�Ot�����A��O�H�C����%�����?�W!ݏ�'�R��#������������[?�F�}���?ч�N!��ޏ���'z7���]H ��ށ�@��H��?ѕH��D���?��#=��'�M�ӈ�� =��'z!��D?��C�+�?���?�O!�0�Ot1ҏ�DO@z�O�8����^�ӐS��_�߽OuO�m�#q�m����
�U�e�<�,K��+��ʐgmF�:۞��?��%�$'�]J�3��A>1#�y�L��W���ج�C��M�s��oC����G��M9	uy�����i����4������ʾ*�|�H���Z�V��8�ou�_��7�l[C��Q�ӮX�6�Q��m���̡d燂vՂ��XS�SH�o�L��}iVSPF�w�t�Y'$�z��6_��m�����r��]����}�⾩��:�;��eH��U����Ux'
_fY�1��4��kLS�˾��"@�����mu�5稓d�u�u�<� �n�r�+���m�+pfەs��Æ+�+���m��
����ʖ`�n��9?�ö�t3�'b�u9�4,V�uv9�e�/iI�?}��>�"�rZVvȷ|c�j�n5I��Aω�J��ڔ拹�O]�#�?��iX��>K>FR�t����*�ZR4o'xx�����K��:��س�������c$����k�p��ZV:� $�jjk�����w�I?=������ɶs�`�c�N�wK�kX��X����zo�R9�Z���P��*��_��]-����4/��	�?�I�ۍ�d�7I���Y�۽��Md�l9JJT����5�8���>GWYIi�Q ���
���(���;��v�x���TK��أ�^ˮ8�	�o�2�������,>�wyw!/y���(;�MO�f��[ۜ�m}~,'��
�ͽ%FV�U����RMj&t�n��w�
)+_�M�v�+�ք��&ٸ-G1#fB2GI�
տϑk�e
t�N�EVv�){mm��)�n!	z��ܝ�C�x����r*x��([�������������.ɩ`�@���?ϣkA�a�CO�m}��qz�D�%�� ��6E�g��߀�n{�}&����>�H[�med{<�/�7dN���礭�(#�Z"��'{��0+ےS<v dO7d�9�.)����ܱ��-� �,J�$KNa1Hl}%�����Y `ǿ!��g=)�
M�A����HRX�w�}���ABc�<y�Kؔ�e_F�:k*�T��hl��'����f�ɂ*����9�ci>WRj͡�4�M�v�:��[��l9;����^9���`�����xE��?0�1�;�6�җ��X�U�����p\�LP�kiA��j��g��!iM�Ye�{_G�a��-C�[����j]jp�aqՁ?�׻˹�gv��!�>�}،�(�-��k
��4��aJ��>�E�����)C��y������#�bm��]����qF��Z@��&p�iQW�QKy]��Mv�!:��2$o74�_�J7�	��>��|@�g�,�ʛ�1����ѿ���PfG���x�Ks� '�E�N�A%
��"S�t���%y� �[/v�U���m�\h��� �����I�N@7�K��9������MgC�\bu����U�3Y�%�}���4�����L�!�4��#��*�*�u1�2,Z���ВAJ�t-��۩l���!�ԫYy���˛��~�l�G�A�\�1C��@>&m�d�+YI4A�ʌ�`O@~�Ϫ��e����eԉ�[[�N0u�}`s�N`����a�U��U .p%	tm��[Z��v�!䏤�.X�gr����m!�rm��ԑ���v�2�C��P���+�,���u�A�b�$��	j�!6k�W��J�οFۛ���|�$�����]̥��4-/�4�&�V�jSjgR���똍)f��͘�
zE��4���++{�E�=�F��?��B��U�`P��j����l��2�y�,�5<@=�"�JJ
M�uF�KZ]=r�&�HN�3o����YuNI ��mxS���eQ�q�rL��"iO:����޿�\jS�5�b�ue�A����R���p=����t�,�u,���R�ڿ��
��-8EMs�$f�m�KlO�����#��h���dQ���͆�d��5���I�����8؞wU���h�lQ���9r[��������ĬN�
�ʦ
;�B.���e��<�S��p��4��	v���nPߞ� ���$��P�� y��^��6�N|}��c����ԭ�`��k�V'πW��7`>ߙ_ �G��z��_Q���m`qp�:5�؆�H���~���1��P���{qkĸS~az�7-��P���(��7�
��*�iR|TH��;l_��c�v�6��W�"Pվ�i��<���`�L���{p����{���إՠmO�4�'��?bV�Q�3��q�	�����*U�6�mF�K���V���u[��dl|�5�ONbVMg����l�C����R/����"bP�y62CnH J�u���Q��	���.��^��~������
�]�7�⛋SweIc%~���~�\���޿78r'� �V���j�-��@;���7r�n�/����c��z�T�OI�I�O�K=�f��^(������!C2#c��B�<j��M��h�el�6�c���z��Rn|;8~ <�O�
ظ@��emW����O+��#��փ��BFp��z�/�>�R5B�U�l�:
{��^��
l�;dd�O'�.tt������6\6�qɛ
eL܅�o_��+��TP~�j2��ꤟp��/��E��<�j�m��Ĩ_��s]��-�K��'ޮw�=�/�g�Ƣ/��
}��.������]��;���~G�b��(ȝ��R�.�����+��h�f��B�oc����j����ϓDj|��9���t�@w�?���#Jn��՛~�^V�����ZC�N�Ǧ��?n\â����]�b�|��D��c�y�:G�q�� m��f�6�]��fT�E?�K$yp:���]�Z,�K���+A?H~ߜ��Ŝ
w�䬠��<Sa������I4�&3dm6ゎ��9��PXmݥu�7+!�l����o���LxWX�
f>ͼ&7e���.�p��I}�/��΂~���;v1�M�Z��7.Qo������u~;��S�����=|��{_�]�s�N�.eLv��#:}�`۸R}t�֞���?È�\�����P���$��8�O�%��8�^��S���~��yS��gI3�3�Rd�J l�'�t�3GX�&�
.b�W^��@��p���Y��ٌ��Q������%G�$����;>����3��<�5�1ڤ?z������tk��MZ0"�v1�@�:�lp���b��'���8�	�k�5�!�6w+$��Qݴ�\�DSv|"���SU��\8[��R���n�3v��x�o�����D��1�8�RGs!W���f������.�L�q�􌥜�	a?���SQR���=���N�*��WUnߞU��w�J��ma�g�������V�������S��g����G���]���������m��[����VI㏧��_J.���h���Y$��b���Yi c���-���ds?�`�(���*��M|�Y=�4�����Kd�`�<Bg'w�E��a\(�l��~�w�!����)Jm�/���i
�w5��슾n���Y��4���١ڋoW�Z��o��	O��P�_����R�K-�?�`|0rg-�"�ϩ̔�Ԩi_��m!�Dr�w�K�
,��l�
�C�+]���W;��M:��G�Ef\<_��c��ѳ�)?N�֟�S|�wVh��A�u��k�d��hS#۸��]��ƨ��
��h5�s*��Y�/f
ti	��-�W����$���-���U4�:6QoWF|���Wi˅�B�`�,�k�Q�٥!�콍�~�C2`@cei2+Ǯ�Bj��Qͪ�j�;�SO���HE��Md�xf=Iq�?�)(u�z~�P��!��Oy�ײv���gH]Q�IG~[O��
2S���ux{���!��P��������w]V�y%����h������O��E�%V�ֳy�ô���Ռ*�|� [���lm������H�E�9
f�J [�H��.�1�R���D� �;2��m%
�lH���\����C��a8��D���3����s�u��4G�v�#'��m�a��5F]���	�S.y��fB)a���-S
��R��-0�X-��ߑ�I����7K�[�����g@?G�ޮ����9N��:>�w� �̂#lGĆV
4
]��k�&�@KX ;����9x �����Y�`��$�C,Twu+���j�'�ъ����
������W��AЏo#H��<�	����N�˾��3�㶄�w�� ��u�V0��>&_Es����4�X��X
�9O��p�m#��װ�Ù#�����a�m��'_����:x��2�Ȃ[�Vث�褗�t�B	,��덆G�C띚Y!	v9����Kq;��!����)����!<p��W_�W'7G.�	B�>^�'>f6"gA��[0�kX�.���*��'��(NNºW����ѿb1G2�^=��5��
���q�验!�v_J���H�w�2�T*��-K͘.�%��4� ������	����V�y#�N��=�L,�>��>���Ż|'{�g���q�w6z��8<��[���û�u9�w���w�opn�nwM�n�e�"�:��F"G��
��=��n�v�^?�n�r��n�t:h_��Y��T�ɍ�m������| �M���BZ��-/����:�K1SSǣ��pA�g�l����£Y9̗���W����є^��^��	�����c�L�'��3���
y� ��뜼p 4i���g��s��7��9<x�N\�o&��Y��g�K؋�<}�n��<��[���q�S��j�>�X�r��Gd�gP{��fP�4�x�/Ŕ�3�	`kb�~8�soN�AT[�-��Q|{�F3��q���)p`/��V;0���8J��F۽���(�/�
P��
p�����`� m��	`��@mP}�C8��
^?d�NP6֧*T�Ȯ6�4$��<��y}��rM�Rpp]����n�"6��J���9Z^nג�=x_V��و/?�s�:��>::�Ńe���VhH�|#��ДJ���\�/�A�I�^Le���p��D�ql~2wQ�|n~���v�$:���S�OQ.Y��m~G�T��مc���������W7����|��)��7��E'�pY/;���O��K��<<J��U�[���,���F�q7m͛-�t#�lޜ,ya�6*�
ʰX���R!�}���.Hly Kv�>��T��$/'��G��h���:��:CXgS�j9�'�B������n;���HX��1wu�:û���(v�j��a�:L�%2��Æ��8���
�_� ������/HD��}���`�����UT~�����j�pl��W.��J��ܠ(�ܷ���56�V��궳���y��h�j���bW`�J����0�4jZzhwr��t��
@��q�	��`ɒ�g'�;%�_G٩�y�Vtε�݌�o���	t��F�g[ۏ�T޾K�#��_�������kv� 3���gV�w`᳗��܀z�7M�����C�ז��C�[��l���JWkk3�1|�,;Օ�n�:���lT[ 3���)�]_���[Q4 current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
      ++current6_;
      if (current6_ == end6_) {
        current6_ = begin6_;
        ++current5_;
      }
      if (current5_ == end5_) {
        current5_ = begin5_;
        ++current4_;
      }
      if (current4_ == end4_) {
        current4_ = begin4_;
        ++current3_;
      }
      if (current3_ == end3_) {
        current3_ = begin3_;
        ++current2_;
      }
      if (current2_ == end2_) {
        current2_ = begin2_;
        ++current1_;
      }
      ComputeCurrentValue();
    }
    virtual ParamIteratorInterface<ParamType>* Clone() const {
      return new Iterator(*this);
    }
    virtual const ParamType* Current() const { return &current_value_; }
    virtual bool Equals(const ParamIteratorInterface<ParamType>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      const Iterator* typed_other =
          CheckedDowncastToActualType<const Iterator>(&other);
      // We must report iterators equal if they both point beyond their
      // respective ranges. That can happen in a variety of fashions,
      // so we have to consult AtEnd().
      return (AtEnd() && typed_other->AtEnd()) ||
         (
          current1_ == typed_other->current1_ &&
          current2_ == typed_other->current2_ &&
          current3_ == typed_other->current3_ &&
          current4_ == typed_other->current4_ &&
          current5_ == typed_other->current5_ &&
          current6_ == typed_other->current6_);
    }

   private:
    Iterator(const Iterator& other)
        : base_(other.base_),
        begin1_(other.begin1_),
        end1_(other.end1_),
        current1_(other.current1_),
        begin2_(other.begin2_),
        end2_(other.end2_),
        current2_(other.current2_),
        begin3_(other.begin3_),
        end3_(other.end3_),
        current3_(other.current3_),
        begin4_(other.begin4_),
        end4_(other.end4_),
        current4_(other.current4_),
        begin5_(other.begin5_),
        end5_(other.end5_),
        current5_(other.current5_),
        begin6_(other.begin6_),
        end6_(other.end6_),
        current6_(other.current6_) {
      ComputeCurrentValue();
    }

    void ComputeCurrentValue() {
      if (!AtEnd())
        current_value_ = ParamType(*current1_, *current2_, *current3_,
            *current4_, *current5_, *current6_);
    }
    bool AtEnd() const {
      // We must report iterator past the end of the range when either of the
      // component iterators has reached the end of its range.
      return
          current1_ == end1_ ||
          current2_ == end2_ ||
          current3_ == end3_ ||
          current4_ == end4_ ||
          current5_ == end5_ ||
          current6_ == end6_;
    }

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<ParamType>* const base_;
    // begin[i]_ and end[i]_ define the i-th range that Iterator traverses.
    // current[i]_ is the actual traversing iterator.
    const typename ParamGenerator<T1>::iterator begin1_;
    const typename ParamGenerator<T1>::iterator end1_;
    typename ParamGenerator<T1>::iterator current1_;
    const typename ParamGenerator<T2>::iterator begin2_;
    const typename ParamGenerator<T2>::iterator end2_;
    typename ParamGenerator<T2>::iterator current2_;
    const typename ParamGenerator<T3>::iterator begin3_;
    const typename ParamGenerator<T3>::iterator end3_;
    typename ParamGenerator<T3>::iterator current3_;
    const typename ParamGenerator<T4>::iterator begin4_;
    const typename ParamGenerator<T4>::iterator end4_;
    typename ParamGenerator<T4>::iterator current4_;
    const typename ParamGenerator<T5>::iterator begin5_;
    const typename ParamGenerator<T5>::iterator end5_;
    typename ParamGenerator<T5>::iterator current5_;
    const typename ParamGenerator<T6>::iterator begin6_;
    const typename ParamGenerator<T6>::iterator end6_;
    typename ParamGenerator<T6>::iterator current6_;
    ParamType current_value_;
  };  // class CartesianProductGenerator6::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const CartesianProductGenerator6& other);

  const ParamGenerator<T1> g1_;
  const ParamGenerator<T2> g2_;
  const ParamGenerator<T3> g3_;
  const ParamGenerator<T4> g4_;
  const ParamGenerator<T5> g5_;
  const ParamGenerator<T6> g6_;
};  // class CartesianProductGenerator6


template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7>
class CartesianProductGenerator7
    : public ParamGeneratorInterface< ::std::tr1::tuple<T1, T2, T3, T4, T5, T6,
        T7> > {
 public:
  typedef ::std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7> ParamType;

  CartesianProductGenerator7(const ParamGenerator<T1>& g1,
      const ParamGenerator<T2>& g2, const ParamGenerator<T3>& g3,
      const ParamGenerator<T4>& g4, const ParamGenerator<T5>& g5,
      const ParamGenerator<T6>& g6, const ParamGenerator<T7>& g7)
      : g1_(g1), g2_(g2), g3_(g3), g4_(g4), g5_(g5), g6_(g6), g7_(g7) {}
  virtual ~CartesianProductGenerator7() {}

  virtual ParamIteratorInterface<ParamType>* Begin() const {
    return new Iterator(this, g1_, g1_.begin(), g2_, g2_.begin(), g3_,
        g3_.begin(), g4_, g4_.begin(), g5_, g5_.begin(), g6_, g6_.begin(), g7_,
        g7_.begin());
  }
  virtual ParamIteratorInterface<ParamType>* End() const {
    return new Iterator(this, g1_, g1_.end(), g2_, g2_.end(), g3_, g3_.end(),
        g4_, g4_.end(), g5_, g5_.end(), g6_, g6_.end(), g7_, g7_.end());
  }

 private:
  class Iterator : public ParamIteratorInterface<ParamType> {
   public:
    Iterator(const ParamGeneratorInterface<ParamType>* base,
      const ParamGenerator<T1>& g1,
      const typename ParamGenerator<T1>::iterator& current1,
      const ParamGenerator<T2>& g2,
      const typename ParamGenerator<T2>::iterator& current2,
      const ParamGenerator<T3>& g3,
      const typename ParamGenerator<T3>::iterator& current3,
      const ParamGenerator<T4>& g4,
      const typename ParamGenerator<T4>::iterator& current4,
      const ParamGenerator<T5>& g5,
      const typename ParamGenerator<T5>::iterator& current5,
      const ParamGenerator<T6>& g6,
      const typename ParamGenerator<T6>::iterator& current6,
      const ParamGenerator<T7>& g7,
      const typename ParamGenerator<T7>::iterator& current7)
        : base_(base),
          begin1_(g1.begin()), end1_(g1.end()), current1_(current1),
          begin2_(g2.begin()), end2_(g2.end()), current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6),
          begin7_(g7.begin()), end7_(g7.end()), current7_(current7)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
      ++current7_;
      if (current7_ == end7_) {
        current7_ = begin7_;
        ++current6_;
      }
      if (current6_ == end6_) {
        current6_ = begin6_;
        ++current5_;
      }
      if (current5_ == end5_) {
        current5_ = begin5_;
        ++current4_;
      }
      if (current4_ == end4_) {
        current4_ = begin4_;
        ++current3_;
      }
      if (current3_ == end3_) {
        current3_ = begin3_;
        ++current2_;
      }
      if (current2_ == end2_) {
        current2_ = begin2_;
        ++current1_;
      }
      ComputeCurrentValue();
    }
    virtual ParamIteratorInterface<ParamType>* Clone() const {
      return new Iterator(*this);
    }
    virtual const ParamType* Current() const { return &current_value_; }
    virtual bool Equals(const ParamIteratorInterface<ParamType>& other) const {
      // Having the same base generator guarantees that the other
      // iterator is of the same type and we can downcast.
      GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
          << "The program attempted to compare iterators "
          << "from different generators." << std::endl;
      const Iterator* typed_other =
          CheckedDowncastToActualType<const Iterator>(&other);
      // We must report iterators equal if they both point beyond their
      // respective ranges. That can happen in a variety of fashions,
      // so we have to consult AtEnd().
      return (AtEnd() && typed_other->AtEnd()) ||
         (
          current1_ == typed_other->current1_ &&
          current2_ == typed_other->current2_ &&
          current3_ == typed_other->current3_ &&
          current4_ == typed_other->current4_ &&
          current5_ == typed_other->current5_ &&
          current6_ == typed_other->current6_ &&
          current7_ == typed_other->current7_);
    }

   private:
    Iterator(const Iterator& other)
        : base_(other.base_),
        begin1_(other.begin1_),
        end1_(other.end1_),
        current1_(other.current1_),
        begin2_(other.begin2_),
        end2_(other.end2_),
        current2_(other.current2_),
        begin3_(other.begin3_),
        end3_(other.end3_),
        current3_(other.current3_),
        begin4_(other.begin4_),
        end4_(other.end4_),
        current4_(other.current4_),
        begin5_(other.begin5_),
        end5_(other.end5_),
        current5_(other.current5_),
        begin6_(other.begin6_),
        end6_(other.end6_),
        current6_(other.current6_),
        begin7_(other.begin7_),
        end7_(other.end7_),
        current7_(other.current7_) {
      ComputeCurrentValue();
    }

    void ComputeCurrentValue() {
      if (!AtEnd())
        current_value_ = ParamType(*current1_, *current2_, *current3_,
            *current4_, *current5_, *current6_, *current7_);
    }
    bool AtEnd() const {
      // We must report iterator past the end of the range when either of the
      // component iterators has reached the end of its range.
      return
          current1_ == end1_ ||
          current2_ == end2_ ||
          current3_ == end3_ ||
          current4_ == end4_ ||
          current5_ == end5_ ||
          current6_ == end6_ ||
          current7_ == end7_;
    }

    // No implementation - assignment is unsupported.
    void operator=(const Iterator& other);

    const ParamGeneratorInterface<ParamType>* const base_;
    // begin[i]_ and end[i]_ define the i-th range that Iterator traverses.
    // current[i]_ is the actual traversing iterator.
    const typename ParamGenerator<T1>::iterator begin1_;
    const typename ParamGenerator<T1>::iterator end1_;
    typename ParamGenerator<T1>::iterator current1_;
    const typename ParamGenerator<T2>::iterator begin2_;
    const typename ParamGenerator<T2>::iterator end2_;
    typename ParamGenerator<T2>::iterator current2_;
    const typename ParamGenerator<T3>::iterator begin3_;
    const typename ParamGenerator<T3>::iterator end3_;
    typename ParamGenerator<T3>::iterator current3_;
    const typename ParamGenerator<T4>::iterator begin4_;
    const typename ParamGenerator<T4>::iterator end4_;
    typename ParamGenerator<T4>::iterator current4_;
    const typename ParamGenerator<T5>::iterator begin5_;
    const typename ParamGenerator<T5>::iterator end5_;
    typename ParamGenerator<T5>::iterator current5_;
    const typename ParamGenerator<T6>::iterator begin6_;
    const typename ParamGenerator<T6>::iterator end6_;
    typename ParamGenerator<T6>::iterator current6_;
    const typename ParamGenerator<T7>::iterator begin7_;
    const typename ParamGenerator<T7>::iterator end7_;
    typename ParamGenerator<T7>::iterator current7_;
    ParamType current_value_;
  };  // class CartesianProductGenerator7::Iterator

  // No implementation - assignment is unsupported.
  void operator=(const CartesianProductGenerator7& other);

  const ParamGenerator<T1> g1_;
  const ParamGenerator<T2> g2_;
  const ParamGenerator<T3> g3_;
  const ParamGenerator<T4> g4_;
  const ParamGenerator<T5> g5_;
  const ParamGenerator<T6> g6_;
  const ParamGenerator<T7> g7_;
};  // class CartesianProductGenerator7


template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8>
class CartesianProductGenerator8
    : public ParamGeneratorInterface< ::std::tr1::tuple<T1, T2, T3, T4, T5, T6,
        T7, T8> > {
 public:
  typedef ::std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8> ParamType;

  CartesianProductGenerator8(const ParamGenerator<T1>& g1,
      const ParamGenerator<T2>& g2, const ParamGenerator<T3>& g3,
      const ParamGenerator<T4>& g4, const ParamGenerator<T5>& g5,
      const ParamGenerator<T6>& g6, const ParamGenerator<T7>& g7,
      const ParamGenerator<T8>& g8)
      : g1_(g1), g2_(g2), g3_(g3), g4_(g4), g5_(g5), g6_(g6), g7_(g7),
          g8_(g8) {}
  virtual ~CartesianProductGenerator8() {}

  virtual ParamIteratorInterface<ParamType>* Begin() const {
    return new Iterator(this, g1_, g1_.begin(), g2_, g2_.begin(), g3_,
        g3_.begin(), g4_, g4_.begin(), g5_, g5_.begin(), g6_, g6_.begin(), g7_,
        g7_.begin(), g8_, g8_.begin());
  }
  virtual ParamIteratorInterface<ParamType>* End() const {
    return new Iterator(this, g1_, g1_.end(), g2_, g2_.end(), g3_, g3_.end(),
        g4_, g4_.end(), g5_, g5_.end(), g6_, g6_.end(), g7_, g7_.end(), g8_,
        g8_.end());
  }

 private:
  class Iterator : public ParamIteratorInterface<ParamType> {
   public:
    Iterator(const ParamGeneratorInterface<ParamType>* base,
      const ParamGenerator<T1>& g1,
      const typename ParamGenerator<T1>::iterator& current1,
      const ParamGenerator<T2>& g2,
      const typename ParamGenerator<T2>::iterator& current2,
      const ParamGenerator<T3>& g3,
      const typename ParamGenerator<T3>::iterator& current3,
      const ParamGenerator<T4>& g4,
      const typename ParamGenerator<T4>::iterator& current4,
      const ParamGenerator<T5>& g5,
      const typename ParamGenerator<T5>::iterator& current5,
      const ParamGenerator<T6>& g6,
      const typename ParamGenerator<T6>::iterator& current6,
      const ParamGenerator<T7>& g7,
      const typename ParamGenerator<T7>::iterator& current7,
      const ParamGenerator<T8>& g8,
      const typename ParamGenerator<T8>::iterator& current8)
        : base_(base),
          begin1_(g1.begin()), end1_(g1.end()), current1_(current1),
          begin2_(g2.begin()), end2_(g2.end()), current2_(current2),
          begin3_(g3.begin()), end3_(g3.end()), current3_(current3),
          begin4_(g4.begin()), end4_(g4.end()), current4_(current4),
          begin5_(g5.begin()), end5_(g5.end()), current5_(current5),
          begin6_(g6.begin()), end6_(g6.end()), current6_(current6),
          begin7_(g7.begin()), end7_(g7.end()), current7_(current7),
          begin8_(g8.begin()), end8_(g8.end()), current8_(current8)    {
      ComputeCurrentValue();
    }
    virtual ~Iterator() {}

    virtual const ParamGeneratorInterface<ParamType>* BaseGenerator() const {
      return base_;
    }
    // Advance should not be called on beyond-of-range iterators
    // so no component iterators must be beyond end of range, either.
    virtual void Advance() {
      assert(!AtEnd());
     ��>MI,����k���8Gj��e�s�&X��jJɇ�-	��q&D�ey�-�v��������'�җ���^u=m��o����$Uu��w���e���/�}�AA��F��R��A�>��t|Gv�#���	^�H��wk��(o��A�rkq�<f0Tr?p�{bi�0���y"���9���ݡw v���\�?�o��������"}��gb�ԋ���{������籜�"���/~�?���g��_��`�����;�O_��`�
�O���p������HD}�����\֏��������A"]��]DzKw�4���o�����e��k{#�o{d�?��)�o@���Wn�?,/t@�����z���\/�����F�t�Hg���"�KGa��M�5w��{���|OD�����=���چn�u#�o������=e��=ߋ�y��`�#"�`�m"ݛ�Wc�<��o�/j�u��+��ݑ�{?h�?^��5���(�w��2�O��X~h����vC�m������O�����[�D�V�����
﷚L��Bn����x�������cx��3�o��1{�u��n�!�ְy�8�K~�̾�������2{;%@L�Q���|NlB+B[u\�_���u�-�  ���'"OC�oM�{u׊��Qϫ�A�Yχ��}ۍ�c(<g��$���-ȱK��#WHj��{�v��nX���}=f�g�����1<�i��#�c��/¥�1�ugn}[�������T�te$��iۃ����P�$Z��L�~S��
���uװ�K���q�Eq��SW�qf�7���FQ+��ۧ�Rϫ��=���%�Y�*��~�E�skԳ���ci��>R�$����ғ:%��ϳ���V?�ܩ7����}�m�S?�6��n���$۠'�Zb��[NF^�I�|oe�n�m3�.�g�$s�G�<c�
-�A� �#���I�O/�_T
Bv�'gV���uhy�ye�eL��!B�W��ˊ�O��q?Dh���[��0f�C޲Z�.��*�/��������}�Fv��γ�����І���f#ϢO�3�F������,�M3Uw�kz>��W����L�:es�l�"M�a���-��9���*������N����!E��G�?���-�v���Cn/� ��Ha:�c.�k!6��/��V�j�X�W�C��n���*��t���| ��<h�fkNF��2�����g��� ��.h���!3�'��ʆ�[���%�f����
�1��cN�θ_�`8ޝrϘ�)'V�cK���BG(8�����q�,15�F�E�DaJy����P D�A�e�9p^�x�WR��Ʈd	����|�FS�$��k]��H^]�ה8v�:
f�Sl�^]����c�x_��''q��6�Z���X�2E��*��+�f�Nu���[�wf}v����� ��
>�Fٽ�B��)��&�u'�^`�h�h7b�^�z�R]X�v1$^�r��y�B���u�u�B�i�j+�w?����ؿ�C��	2{#O@�����l���|��Q$$�Wk=YD�x�i��8Վv�zG�/���������ըS��JY�\*�Y�`����'WK��䈵\-���j+/�����󏉺I��\���
�W�o�(+���&Kf����\p����p���zz�s�S���q.�{,�{,�/&�'�k�n�n��x�ʫ�z�)��
��V�m�ZA���g=�%�"��'�$�٦�lU^�|��7��������ܚ��о\��T������о���5N��J�G2�[���G\����dq)���x��_�m�Y�HL>���5T_}�����_���_d��#�oi�ٞ��|&b-��j��jy+��E`�C�e�ݵ����s'����6`M{�玂��v%+�K���m1�5����Y�O�V�C�S��J
v�~yI'�sL���H�5d�84p=맷&� W�$��9_���~3��iI���$��F[	���ٝ��M�A����+�_����cLW�����}#!�Е�Z�ٿ�s�9��P���s����Ǡl��mŖ��jf������?��ӛo�VEXԗh��}ҫd��5���L�\���	뫒Eܞ��*�A�U71�A"��D�����0�����$�g��J
(r��H����0��J��⽆�ɤH ?J�6&8�.l-��	\M|Њj=�:��7J�Gl��T��_I�&+j&5����<�NG�O��
٭#~�n�����~����s!�8
=��rC�]~���by��Ʀdh_8(�>�����<���2�?`�AF�����<0��k���`�	���h�m���r	=��UU�=�pS���x���Mp4(_��C3�ŀ�Y�l�ւ;������}�ǰ�u���6<�@{�B�#o�A�"�T�)d�?�	�z�S��������\��/�#�j�NC���j����I2� �ܮ�p1�7�biW�)�
���V`�D�O����j� �8��WE���a�gۯB���#�ϱ��"]����q�L���Х�㚞�a?A�Wf�?"}�}�"�g��A�۱�C"ݛ��E:��o�oY:J����.������#�&�o��v��Ɲ�秵d���s*�̩��h1��%+Rn�mz�h
@Ҏn�+�?�b���E������Ol}�<şq���fh�������/���>}�x��$;[��ͭ�'xih��}X�o ��%|�%�&_G3<�G���
h!�8"����NH,���d��V���\1�}{)�_�>��O�	x.������Qݳ��,JH�*`�(�
fVȜ
��'���U�"�5rv��qS8ϙ�21~p���럑]�:IvW��af1�������Q��u��wt9�Z��{�ʢ D�н~��vF���������h�P�B�=4.s�����J������<�$�߱t�^��0�+��b�n�ko-��2��V�d�VAQns�q�Z�����.B���>K�ZICQ,����r��T�G��}·�}/�� �6�t����;���3�W��X:^�[���_��f�(�����~���,}D��`�m"�.K���0�_�?c������:�Ƈ ����(���FRQ�)q��ːE��š׶�DZh��M|��A޴���������v.չ*&`�G	|�����sx�Ezo?�i� ����D��q��RdN�q��.�d�����ǣ<�0����|����~��"���T��Gv��)ď�8��<ؓɿ����R��?8Lr�����}a���&X튯j���9�Ȋs��lWu�)9�|������s��<X���
��K�8|����%v~���ӫ�����ˡ@Ю�/�=��_H�r��Z�}�1�k���fI='AڮǠ]�k��B�}�f���?���3�� ��b������"ma�V"��q"��?;Ok��,�;�{��Gw��8��꿋~�9�j�'|�*�)c1��}X�M�'}�1��E����A�d�1�{E�w�7����{��KYȠa�a
�Ӿ��`N����W���6t��~����J�~k�y��H?��ߤ�	���+��hߠ���������
/ �t������#R����ӣ_`h�v?aD+SW{�\�^���{5~������3M%j��=�%g(js4U?I�̔<@e��Ϡ|?��h)��}M��BZ��˪�K�Nz�l�w���������Q�&M�7Z;����>:��I�2��A�'���X~j�>a�R)���C�'ނ�[�[�Amh���i�
|�Qe�o��	�!l��u���Za3
ږ4j[fU}��ƮW|n.;i��V�-Y.�Rcy�Ѭ*�_�������A�
۵����%�<�E�_�����h�c�7hO��=����p<d���8@�yG��$q�o�ߧ��%�>�7_�k �y�b톏�]�ou�Y`����I�I��.5��C��kLCG��ROA@�b܁��;u�n#M���{��Q<��H���E:�
��*�-�;�*�e��mBê�8����{5{լ�/��,x��E�]H�#ޏ�W��ĹfQf�gw�=B�����/��ɩ���n���T78�s�zDl�Ԡ�[�6�������w�vއ���wxl�HS���#!�~pݠ^ �+��T�ҵ�_IG�s�|E��kRi��!+����)�җ����C
wT������� �1�w<!{a�֫��d�W��XiE��`y��F���ZYR�v�`6�}�$=
�`�X�K��0ԳRX�`�֮"��V/��-/�e�%��b����*����/^��3_l���|�9K6��ZO���׫Ne=�`=W�H�7��Β���=8�1�k�i�%:�������o��V�7L��TI�7\���<��d�Ug8������J�{Xf�+�(L��A�r�kz��L�;�`r�����V�$c9/�I�h{��z۪�X>$T�/�ǭ�W_��޲(��<�F�LF��>�Z~������/&�zG�ϸ�K��\��6O/�������&�cYz�H'���"}3K/i3�ϼ!���)�cnb�?YK�/Y��H���D�0�����,/ҩ,}�Hd�(���9���,}��Ad�FL��������"�Ű���ڰ�"]��g���z��"=����,�ӎe�����/��<"x�N���X]��������=s>���b��G�,?�B	u<z!+X�U'w,S�:��L����.�D
lQ�$l?��?�Zܣ R�N8ψ����C4����%A����(�6��	� �R�+�w9��LY������2C\�Y�LO�v-�W��[7yx���� mz�jqa���j���}�c�Nx�Գ��,~�o�M�%�9��
X��X{�wi�4��؅���A8���1l�S+���F��o��ݵ�"���H<c��<�y��2Q`O����`L���ǝ��9��7����p8ׇ_()Γ������l˂�v�����Y�>t(J���J��;@ˡy��1#��_��?H�=���;�G�_�\�����Z.�߰@�o�[��n���?�#��M�g�
�uyW�\����g�\�f��JɎ�~\�pnTx; ���4��C��<��ҵ�O���������p'	.�������#ՙC�\�xAO��nX���2_5�y��,�u`�P\��H����Ks��Z�̜�e����2E��Uh�vnv8������jr��z��՚MC��|Z����Χ�§������O�>���i]�Ok��Y�ӎ+xg�M;�͘Y�0ٽ���UY\Ly����T�,&��v*�O�� F�)����SM,���7�o,,5�LPI�]ؙ!3|����g���I����8͂p��J
[
b��Z���J���
�TaOOގ����6��}�Y��Cy����L�k>�8|_3nQ�������6C��=SS>Ԋ���A~�cvJ��A{jʷ
�,�^�c���4P|�����2�p[��f�QQa��^�ռ����8�sh
���f_���_��#�zy�?�\e�h�dV�~����F�::_l��T�n� A�6M��#M�Qx��v�Ԣ+��=d.=R�{�I�#���z��џ�	�%U����|YE�ק�Hd�Z0��[�y2��q+�qƣ�2J�����ytE۸�Z�Iw<���d^,�0��;�����_8�Pf�A���ة��n��q������Q|�1B��6ڔ�C�N	�u��Mv����88B=$B��Rƙq�f��M8��I��7z���r�7��?8�U���X/f�x?�k��&��%➄�� |������0=��7$ԃ�c�؃J��ѿ:A�Jq}�'zՇ�7���ߔ��Y�����q�P�{^>�p�Q�1��Y��[����X����'�5�yH����Q�� �������L�X:yy��-7^�>�F�EX�������a�;��V��m��N�$�ƻ���o΁@v+�1�k!ux.�F~��k5&S�=�ܸ]�ޓUϏ�3")��Pl�uN�g��)fD۞��ǲy�<n����XM�n����bZ�4�������Z1���ҕ1����7D�X�#PM7���D��P�9Q�Ƭ��r�j��2��d�2�G*��%�,�����"�w1�<pP;�Q�O��b�)�������i��^��	�&�׺~��K��O�o-�f0�I��Jo���wy�F��x�&��{���{iO���,k9�ͻ�*�I�<�X�,;�W� {M߆"�yZ�L q��΀�C��Y�����.�^�.-�\	�<�9t�!�]�>����o��r�jӴq���0]�YӤ�����:zt�����rm��G�BZ�G��w3��}N��9T̝����Ib6����xS��R��Jl����	[�@�t
��}5�p�x�>����Rj���F|�����fE��B$5�>FGc�u�y+>��CHw����9�1r��k����
�(X��7�GiB�s�*|������s��93gfΜ�AI�^�rw����Ll�I�߈�7y�Kb�����PR�/�c�O�?�5)ߥ��IR��X����8��H�ω���x����t��i����)Q�WiUe��}kg{�����y��[E�q2� ���	qz��JN��"���!�pY�Nv���Ϧn����a!�O�#���r�~�q�:o]����¦>t�$Of`2]��I&����'�a2C���^~M+<��?�x��\�A�BG��:�u;�u�n֢�=�#��1Շ�:�z��X�' t�#���t�D��\�������lc�?�:�G��7���_��R�����f����60�˫H����q�lWXխ�t�<�Yj�y��섬oy�=���F{xV�׶D����Y����5䖷�u_
�F$��CX��=q�H|h ,ū��ip����w�����;�QVύD ?E�E��2#��D=�:=��t=�SXw� �}����v� ߌ4Tw�;c�"h �5�@�{,�o��,]�N�~�?��ˡZ7��8Q0DS�"�/'H���6��KJ'(&'�����vP	^�(d��DNv�1-l��˃߹X�@~"� ����n�<X�y��8a�+��#.y0�x��Y����r�!��ލ��N�|'^�T�R�ek���(����(��9����Ri�`���Oi�_�Bpo�6w|M��Gb�5=��˅5�6���|J��+Ԏ�e��T�y�1_J��)��ҵ	�͈7�&����X|]��\^�xX��PHs�Ɉ��P?H/����DE]H�|0���0]=nC�(�,j}��� �毄E�˧����Y�p�n��Jb�v%��P��ʭ���k�~�cY�=���p:꽦�����u�|t|>|\��	�OgT}��Wa� ���Y~4�`y�.̇e�{�rhh�bij��y�c���
���O���ѐ����Ԥ~܃�X����aa?*��������?��z���%������BU�FT��ƫ���>P��i*%��a�+�H��w��/���
�ܢ���կ�#�g^�(8j����E����s]��������s�}�t�W�_x����u{V���+�c:���m�C��Q��V+���h�~ì������"ku4r0w9�M��5x���0~��8>��r��R�Ղ�����#�~
��O�{��ǣ������}7-�;2�ƻ+偧&�^ɷ������9����!侟L�~���״6�;r�pI�O���`t�k��n[�w�a�B��K�D�6�>�����GúL����&D}%�==81��9?!��yBTqӥ�DԺ�K���lr磿�����޿oCRX�D|���nd]v@&�vBH�����j$0�;��z"O��S�<u3O]� ߞ���k�)������$�:�Sw����4O�n��O��~p��C�gI/oK�d\<���Nj�mi��/%F��TύZ��H��1���]��P�~t;���x�QT>��O�d�?܀���܀�>���Jt��?J!���iI��D�̪�3�W6U��dD��O�'%Q{q��%o������f�<�g�5��Po��~��G�N<��ǂX�F�O���� ��;`zL��?5�"y�z֗����DҘW����K���O������f��k�5F]-7�0�M�p|R����oX߹������'��}�7������)I������+1�������w_V���}�=w'>I���<z��QL^4��4�B�j��_�+yviL�X�!����<��w�~��m�":=q�UC�S�P�KK��J�����T�r�z����J/�	Um���^�P��;
�}Rt���E}m�]W���R�)�U��� �@��Vŧ)VF�+A
��;̇�²�1D��A�"vV �U�~9Q����^�Ͷ?Z�4��Oe�t�ӫ0:�/�����Q�

x�k���b�.�� ҙ	�b15E��"{i5m��9�[+���JVʂ(�1��4�]�O}���Ji��x0�<��_�x@@�X+EoP��ƀ�=<#z+��-�9EX+�Ͽ�OU�������#Ha7���߬�݁. �� ��t4x���Zt{�k_�����_-��f��;r=�<�(�k��r�{.���y�:r�E�KW��۠*h>�1T��� �iǮx�����Nw��-pD�L,/���n6��b���l���2v���b�(?�ȷ���M(�B�|ޭ���}�`˲��`�oO�W���h��˒�6+K�(�٬,o]4��9997�����,��zƑ3=*����ދ�gIݱV+�R��k�fjE�!���.o��L�%�|����g!��@/s݁;R ���؟��b}%��>
�,�u�d,�Q�Edݶ�>���mTc���_i���X+mc�������lL�r0���E���OX�k��?�G�s��wj�C��<�_��l����.�	���(�X+�Մ�EQy:Qx�XB$�W��'�B/4�S�6B��h|Z��l�l�#S)�{��%?b1��Sa�hpZ��������f���v��"�v��.��@?{�Òm����<Z���Ed{���w�G��L�	6�:�g��F��3�( ���ͩُ�/+,;l
[V�,�9u.�p k:�.���ʹ���^5��H��۞�;e�%��;t���P���ә�)q0��9�ɨ��b�|��~�C�s����N��b{�.�9��wh���T{.q�O��E�~����Ϫ軅�]*��l�xw�1�ޣav]	�����~���c�������Q��/�D�+$�+�q>��c�$�����%:�8���A�,c�A���Cx�'����Ko�;���'x�;<��a��3_�������4��w!��n+?M$$��'����͕M5��N1��NTn�����
;��� ��P�T�n�-YI�w1.������&�[���\��3y���W�fy0��!>�'뢵x#��[��$*��;ͼ�>�Jo�\XU�4�t8J�rw`�	ȃ���:�s�GTt��m�,
��K����9�Y���~#)U�Sw�L:_��E9�����+������Y�t8J�}������E���
6�f�����W����;g��_�4��/ٍ<����B�v���E�\�u�h�ct��d�*l�f5���=��a�j\r���Aٮ�ʗ�6�a;��CD�n��g��l���	H9^��ۖ��ؾ�5���g��Qz�%�Y�Fi���לI6=���Z���}�I�?$uv�[V��f�m�r��� �,z/w��|#�\ѻ�Hc��z��܂�}*� ?�&��A�o���:o��m+�(��4|���\9}g���� ��o��G� 솸��\��X�<�(��V+cè���j�B;;o����'u�ߠ��m�W�w&U�:��C�ׇE��×���V�XX3B���G�:�װO#!�*��Tۑ7莩��; Y
ъ(�I�\\�~ <� �Tܥ4fm����?��aD���Ten���Mdz�i�V����
�;%�������FD��Z10j�n1��P�U�1�O��^��<������'/�h�����慫��o���Ϋes ���M�>�E`��7p��;�n���@z��[op�6dO�FϹ@�z�]R�� a�8
[�, &%8?ށ}Q�<�gi�{*�<�_�7*d�\����o�L���6ؾ�O�=0X L}q-@a�h��繖H�P��8ǆ��P���f\�,�r��qHe�?�G�{<%���
���zp�%RR���𵩾8�G'��;�@�&v���d�^�/����l�ń�90����.�,���h{����J3?Z�A5P2H%d-'�A�%�gw`�����f^�۰
~1�m�jf
�U�	�>q���_���w9�1��͍�
�[�9�@>
5G�E�Y���U�����%��B��c�A�u��F@�A"q@2�^�PT����i��<%4�9�Ң^���%��mD�@$P&5�O��Ξ܈�:�և�r�`�Q	���c��##�&��e�)��lC�e�r�q��:�>H5r^�L��t�0X�E��Ք�
SI���='Ey^�;0 �E�I�?E�p^R�}����%�s	~<�;��<���q� WS��s��n��Ȕ����-�f�z��������pFg]�'�@��P�>|�ε��� m����H�R��A
`����d��5QD8n�n����:��(��y�;�2{#�����T��N5�nێ<g5'	�U���i����F��>�\��M������#�' F�f��5x;5�F7��[���H����j�N��{�o�k�v<���D3�ߢc�b��:��	�-ͤ� ~��F�$�����/�K�#�cnv�S.'�l�)�D뚬\MbhU�-�������č�^L��\��.�·�7�Z��<���#��l@�{^K�\��n{�C�T����I���_���W���U-���{
}����b����B7���9�n���Fd��e���q^dhFnM��=&���zZm�Q�@kd��m~h:`mR��vن�v�	_H�����6�>|#ZP�yG�O�_�x>�@�qW�Ȃo�m�҈
�R�>`OYW�s@�=�v/#҈�Ocە���gKc�jҴ�H�9F��
rf�H�"j���jqc|�E�ԁ�P/��Z�~h�)ܡ)?���w+ �'"��^Nq������c_�W�����>�^�M��W>��A#^`�����J�������H���5r{v����ō��߂�$�)��0��r�3����a؆��xL�>�h���`�wW?I�j�A���l���Ω�7��JCPi�?�c�&�p	/��l�M���Q���ǆҴ1�Z�^��=���n�7���5��o�1�W]B{��ҿp /��O�3����_��������?/x�������N��%a�?m߀s�^��[�{�v
0@�C��0���Ѡ����x w��(A���5�(�2�B�����[Y.���P�[��H(���5k$J7����ouP(Gť�W���"��]^A,�v���.^�>��#I! Gω�0'ܹ�5��� �Q���x��l1��KZ.�s\�yMt�Uyu ���v�J�)���r;� ���Wf�y���.�
�B>˷��	.~q��d���7(é @�g����R=&�I�������~A�h��^�Q��f1��&��0]��.��]&��q�������'�L���`C�
[.b�F��責���A1~l	݅�t!�:���9aZx��A���DG��~��rt����� �YO�Ė����t_��Ռ'ˉ���x��I����<�4�o�����^v`�MѷZhE�&<��/�U9��,$L�g0��Fn��.:�M����2K
=R�/y�Jd*��ha��[���ĵ��sz1��K n�;X�w��]f�
Em3�,`CDw`Ȝ�{`p@��!�f˃�wjjK�BͯݶWd#&���多.�,Y����Ĳ�̀ږn�xs�1{��v7��<�,�Ik�5.��-q7�b4 �O�.B�Z B�3���PHM����)��G��d�f&��TU�|/,��ak#�\��+9��ޗ�#�pX"��q�8����@��N�,���u��m6t;x��
	!�ξA��t/�����WK�	�rYd�s�����j�� �����;@�6D�����0s���4��4AU�2�Q�����~�^��Hv���_�)�l���Q�\��/v�]�H��A�K!�<琟2:mO=��)�2=���SEH A��D��x������J����}Z�tǻ��zC�JJ�����S9�.&Vb��7H�����b��j�@^�p�I�(��KՃQplw1J��%�0�4q�'�冒]�R�
菩��s��<�
d�?����H"��6
��S��t(̟�v�������<@�S�����E�ۍy���s�M����n�� r��ƹ�7Ϝg��9(�L2?1�t�T�A��~�(m��򞸙��5�z�) �B�[؊Ot��%B͐�J�O��l6�\��ڤZa=���!��Y;Q�Y���V�7E�J�Ӽ��TF!�m�Bd?�iY D 7���5�F����ӂ6���G�����+:�� ����)e�-��J���Y���Y�͠��ߣ�4f$��u�Aj~~�隨�H|A��^5���xN�5�w���y���{��\��u��w��*��,�F=���Y[����A��%���+�Nj���V+�Lg�:E+�*���b7�&�f5R<��p����B|Ź9s�ژ`r`U2hݔ)�u�����
�Gf��;����ޜ�RL�T@���wb�����{��xR��������f,��̖�#�
7[�pNɚ�HX��r�c-��԰�3o��'p!����oa�6�%<
�����=`��t�]p4@�S���>��w�!��q
NW��@�ó0`ne���?�t��C�`��vk%P��|��fr��(gX�QX�T�
u���s�����W)�JT�+����9�@ų�Jd�V��.m{�o���枤F�	�w����=�tB�W������ʁ�Qi��>cH�N�G�6���5�4�<����ƝL�G�������	�eg{��W[W`�L�6�w.�h�HV�̆����ib�P:��Z��Ѐ����b�c#R�;gm;�YR��YkeB<��	|��a1b5u�<� _��~�\������E��b��ϯ5:�f�}}o�8"���VMOl�;<��g�v���gC�M����1Dk����v����o9���	BT�o�ԛ��|����Գ�/L�b�����nU�T�w:���Ӈ3�"��x΢�yGh"67�q���=W��t�Ƥ�1�U�
k�_�l�~M\~l}�d���OL+�Y:M�8�\<y��2I�j�2�<ǃ�˫�<��c�4s�Tf�]6[��{JiY񬙳7L����#�T]�ү*Q��Dj=~h��/۹=�h�ڗ&K3�I3ō��̓�N�}��U2O~b���ɭ۟R:�\2��qq�y���i��o�q�;�]�p�{ho�$͜=�,n�:s�bif��u6q�0�V��y��)�+�
�A���	�A���؂z��*� ��(�b��f�]�k����.N'�����"V	��6Pnm4�rm�/������4²�)�5�K3:S�BJ��w�Q/z�+7<�Bq/�F��A�J��&�@r�+ D��F%@J���f�݀����I��R�'z�\�ƏƁ��`Pb��BxV�@6>>?�k�t�H/hD�{�^gFxS�>l�����;�H�oj�;4;;�����(�'8k��H�U�FNUkՆ��6��GU�'Ň�=q�7M#����/�?h�-�ĦSb�J�`�F�s[��93l��M(
2��Ȃ�	��r�Q��a�Sy���U�C��k�Q�ƅ��5p�m=5���(��+Nh���I7�;�a�xv�)M��7AEk}?x!���G
�&O�&�O��Py�&�_$���>�����ẋ] ZQ�"��ҿ؝��xwE.��/���<����~�0y?�m�
x!����)ª����
��Y8��hC�����i����f�ז���(�w߻[���\��x)��IX�}�-ΐ�	���G ���ь:ّ��.�������Us; �3U=ol2V��I��?�M@2���0.j(�@�̿��&���ĘhXG��9F`AG�pF��$���|�[��_��%���f|��4J�a4�XV*�3��1/	cE��
���}�{� Ko`7���l���)R�c;��<���v�iWb�\�"���e��
�4y���^��
o+�F� �럀��l��$�wL��Q�$l��%'k����B�[�/9U�
����|���qO6������H�\�Nu��ľ6w�dE������9��C��z�d�@�Mȳ5�B��������c ߈���U}+���(:a��3<Q���ɣgl�ٕ$�-C,�?�
����M�E��}g��j�H�X��V����/����_�v��6*(�V�W%��#;3��$���ȏ��k�fb��T^Y8����դ~�Ƚ��M���T�Pi!f���˥�EB��O׸��Ĺ�m���a�͡@��Z+�0�k	�+_
զM�I۲(jIӤ
�b�23�����ৎ:*ԕ�H�Ogp�qCEM(H��5�9����$m)~�}?�$�{�۹瞻�ה���oV߲�����?�"U�ק*�=jv�>���a3;Y�0:���A����y�!�>�L��0����!2��o2�����t�X���cn9�0���~�_>�k;�n��9��k�ԪLMv'��2�����ӎ$B3�+X��"��E2��1�[0�΄B@	���t��]�����b����E:�	�Bu��wva5�� D���w����@�~Tj�bE���,���d�-̶�C];�@n��W������7��B|�zQdzX�Fa�t*R1�NM�u��y�T�'�]�ʐ<��:�n��q|�^�52R�W�b�C
v�
Y@u=Ğ�
��E@��+P�_��w��kJ�̡�/����&߮��MN�����/�o7q����b��p[�6��
�d0 �\���A(�ob�܍q|����L����������.���v0;D��ۡ��P�K��� ��F£X��^i����r�\v+-�P(F(�4�6��
<��h��ayz��.���+�2]���ӡԧ���IU���5R��T8���o
�`m���kR94Q����+�p|�搁.�l�a4���ӗ�벒p|�A�������c0�db��@Y�BI�˓�(fVo߮Ҳ[����&I��ޞ!lk-
��5�m�@ȇe�)I>�O������ݱ�Oua���d�0��B��}ۗ��t��i���[1u���ę-V��ӗN�_����fl�LI:�e2��fC{i���]�J�Um2&��-f3���i����Unq��vg���P���}�vK��Pvݍ�hTbTb��
�}Tm{��+���V�R����_`eۊ���B�l[&�wP��R:�ʶ���qH�ssBy���
�Nq�.���F�!�EC��-J��������+S�^4�:��d�o��H�so��˟<�'��������'{ʼ�e+G���}nG�����V�˓Ʉ�K����w�$=���[ ��;���� <0o�����ֿB�B�@o���ª��������t�Q���%�m{^FLm^������'�������F�i@}A&?+���;w���������#S�0�-��H��~�,�9~؞�K�Ծ�=������&��+ί(!d��0b�k�6O1&#1}+鈱��1pu:b�q��@�#��dh��F�&k=����>�+��y��=՝Z�I�柉�7�xVS���ü"J�:I�=K�.����_���t��F�S���q��՝�cQ�,�
�u�M,H�oW0J@����D���GDBrb'�v��6�z�����D�����MQo��d/��)�L���n�7q����[������v��h��m'4��B��%�m��N��\�������`��E��1*�ɋS�g�i�n�N፧q	��:��� ��m�D���d�et�H�	��e��+��:���j_�*��h8L�ǩ�֣�����]?�m��\���|�֢�B��w*�Y�%����8��	
�v-�b���
=��h�?N3� 9�
v�Ѐn��1�O�Z��r~O8�Y�C܆��n��F,���hH&�y��r�
��%��q�YMG��0(:2
�/�~���~�T���ka\�M�95l�D�&��6���K�ú!94�;������]�8PyX(���ǻ�z2�H�������/ڜp��XVP�'A�}G���$�aD��е�w(�����0���ۋF��Z��#CK�_/�g�xZ�|"��f	Ym�/����п��T�v�d0�(*�[��D���A�a��E 5T��!���.�nmn�jb�sTMDg�����R5�YT�P�9�E\����s��^�\�j_�Hl�m�b��$>
������쟯�Af���X�w$KK��۝�]������y@�ܞ��12�핣}��-����O�z��N��X>��#~��k�rh�v�r�o���=��3�����|`�O	3i��.��]~�{�_�Ry����z~8N֩`�� 3o����Q�̗��J��]#��G�/�
���G~c����U����4_Ş��kßӹ�m����<um��{���3�>���=��Qy�S�;�xO%5�
���u�AE^o�ݚ����z��{Z�Qm�f۾�yJ]����h|���3S�W���^A�#���^r�_�
�Y�iqʇ��m�TAl���f#�	�ˠp��n�M�-�c���M�*G�_�{���%��)��K�Sz&ҕ��7����F�wP�H�HB?�$�������w#�		��Y����R9�#�#��O�#�	�aJ�ҵ�˔^��,	���[�>VB���>�}���F��z���n�]	}�� ���?� t�K�����I�i��қ$����_#}���A��^ �oZL���I�E��GI�-�>�?���+��T�.��|�Г�����A��@t�Y	}*��G�o$�*g���OQ��H7I��(���I��P��ϖП��F�_.�_C��+%�zJ�E��3Q����>��/�y�Ч �z*��F�'$�	��	��#T�ǣGB���G�[$��(݊t���2�� =KB�N���?���q��85�9uZr��n�N
h�)�y
��}��U�kr:����e�..4r
�sV��N���рk�鼿VuW%��V[��W4�a>`ݩ��nY g�^�f_�$�I��4����mt{v�*h�Y����ft���'��j|_��5�FDC&D�������'��/#�b��Ʋ"���9�[���z��$�\��:���k�R:����+���YN��A������R��L��v�
0�F<�/U��؍���݅2�U>����:K�QFgi!i\�.Nv'��Q@��b?/�-?��
������Q���Q�$t�Y��O�*v�|��pI��>̾0C]��rȺ@�ۥ�g��v�r0��x���=���MF꼉�ܣ;�sIq��5P�a�x\�<��������H���W���e��ɔ0=Jϧ��7�4��3�9	�u��	��/@��<�f��w�z�}�S�s,/oo�b'xr��H	�E��t_�Y�!#K�yx��:}B������"�0�?�����Ay��]�2����+����2@��.��%��c��V1w�?Na�h�w~�t#�A[V�2Ȉ�Nu=$����zʻ�p{(�8�4��!�_
-�M�O�W���<ݧ�;��(�(�[�ժ���gi}�������Uc�5A��`����a-o����8�����#�0�D�M&u����s��0t��ǉc�O���������v9�٠|�8�����X���n����7�B,��i�>��/��ΧH�{��&;���c7��
���K���%�0�K0�ߞF%)���=���ҿ�Y�f�cihȑ�W�d�*2^�e�*=J���(ms����/�p �#j�9�7�qυ�D9�$(8�
���(�%�Q��*Mփ�H�r�����}Y�0ޗ�ދ��c` �-��Z��0���N�~����l�:x�b-/���WVB���rީ�+�`�MF��y�{9��L��YA����mվ�PtV��z��qT�vR�Q=�T�S���J��]h���
���/B�q�*�ٺ��X��H�IUU��2}~w��bv��Ѹ
��MEȎX3�L��uh)bW"vbf�J3!V�ح��B�Ħ"�'Z�Ɉ�e��X����1b����j7ʄ���+�1��EN�G �Ć#�b�{
ĞE���"؃���?��~�I]����4�'x�Ǹ2!���%��������2]��O'˾�O�`xu�����`��� ��A2��0��d�!0l�).>Cg�
�ׇ�l2x��[�5g��� ��O��^0��"�����hEO��k>���k|;X�{$�l2�����ZV�����v!�ʽ�{0�럑���*6�X��ԓ��i��y2a?K�佝�`
��\�!�����	��A�m��W��otbwl?8Y��%.BG���[eS?�<ar�ɝ�rgJ��ZvK���
K�\h�x��'ާ�ZkO�n�/�-݃W33��g��]]XPº��/�0]�ޞ�l�Ux��͑��?e�c���V�'U��7(��Aw��A�]�?U��L-�-���J��VB2���'�5Y3�_N���2r�w��_������4�B�em��Ȳa�o9��
B���#]���/��"r̀���V�/"B�,�7�u{��AL9��*����^�ڭP��P���LXk����U�ڭQ��P�y��5��?'��HM�K����5��bEu�z�ا>��C��_.,�pQ�"�����u��{b��B�v�q�J�v�A�ⴏ,،��c���5�>����5��<��QYX�*4��+}F5*�>@,tR�C"~�("u�8�<��2x3�6.�d��l\ ���[�?y/��}+��HkP��'%�}A�lq��Fd��a5�u�����{�Oi�g��ş[�� p��7��
�d(�C���-
�Ɨ��Mh���=A!^J6<��ۉ��V�Thh�
�3̃��2ﳦfSwCt�I>	:�_FX3��KA�����L�ӟ�6�Rض���!e�3�W����]����(����Bݩ�V�'�Ii ���S�ŅD ��/tk��
s0�;��2[C�Ge�+���(�YH�Nh���&S�	�c���>��B�k�i��1��"	VC��h����h&B��}��-��a4�q�	t�^HR�K�/#��}�;U��ҕ#y�l'��_ �}���5l<���$z�&��A��9^zK��aڜ0n�i}�V�_'���C{������!��e�4К�M��A�";��F���6,u���9��e`BO�@*�Ha�nA@�j��f�5Czu��wJ6O�M=�{�n�Y6͔EƮ�p)�R�a���[ϖ����O������|`53>X:>z���c\�Ő���z�i��\�q�2��է�����;L7P��[���;��'��T�E�;�2w�)�� �~^�
/3�_B������y���F$��$�R'�}��u���t�/�^&��&9i�^��t��춉�k�d@�������z{z��Qr��c�k�'FZ��7Z��F��s�x�e�\���3c`
Y9O��o�����l�j�#�P�;�c2pJ�:���f��18X�n�Av}�wמ&��6A��A;���/I��+�����ͩ��W.A�rd�����,��2��tؒB�u8tٚ�C���Q���&��&�
40M�saMje�:�V'D�U
e'q���~7�B�� ����qb��z��A��}�/{"��I\Oh���E	obO��go����\5�'b_�փ�8Wv�Ea|�a�2"�|,�Et��eG�N:Vr{�/Z��Y�z"2هƐ�:�����=�]w��Au��'�2�����t��A%��#i��r�p�Zlhl_��[�9�Ӊ��wB��l��~X��4�{����D�#(���h�xS��ń�o����9��G{]�`{~���}�D	��x��?
2i/�tB���� ��g2�_!�L>V��bH%�2t�[R��%e��[R��%�;�%�yU*�Y��G�~-M��[R�Uݒ*X���vK�P�-���[R�<!0Ӻ%��$!0��BE��lH�-�N�����x��\�Iph��jq�����!�ǉ��� 9��`�~!0w�8z�#G����[*&c���d%���L�H�@���&�.="YE�i��;"�!�� ���A�������!�A�1 �s0:@
�=�O`��$0y~�i�xn��q$�djg��x_�d��#Y�}�����p8�M�y����~8�`饉�_�KW|��I�xIe|���%��	�RK��%0$�gu�.!�/%du(1�W�IjT&H�M��"e�$�!2w��q�4�P��-��'vnj<�%�<L|��D�Ϻ�xF$���M�y �')��AxZ��G�y6f�yB��\L�92���D�K�X��'2=W���<�$��f{�:E"����(D>��m{� �5�8A���k���7�߁7y_O·F(DDŶ� ��(XM�k����a�Ǝ�/|FC��MՓ����ǟ��+�<4C����:�8������x~�R���e<�>�J�0L�%v�3����u���_+P3��#����T��{:�Œ~:D550��:�ࢻމ��y��O(]t��^�1 ���i���m��_7%p͍��K�E{�d	5	v���阧��:Ꝝ
b��u�ar,9?�����A��D��� �:#|m�1|K��<�Ѣ?�X��Ai{NOdXJJ��Cg�2^&i���ҜƤN�����뛧HK7�[���Ɑ��ugT���e��{�{޲
֛ܛ��_I�wo��|�:����W��z�v�F�_�n!
2a
�.:'>������ -wD��s� ���������B���<�M�kݵ(�s�>�s��]�=A$�s/�̤f�}�OPM��F�X:R��3���$��Ϝ�����y��0���_-�kh���gc�CK�º%���=�����x����/�qif	�/�'�:SK����H1?i���L���oŰ��0y��w�o��`ҏ��P��%��%�f�(C�ȏ��d��rd�->�
pF�_�g��.�}�� �t�˙2FMN�٭7��}�����YZ��z���}�n����tg���e2�sn�]''���f�p<y�VyF�e�L����*u~�:P(c����;��`ވ��1{Os��s:���گ��+q��6c^{z
0ۆ��R�>?�	v��d���9� >�.y�
���M��J�r�v��PV���li0�]v�
��V�c[a���q�ý�a����[����fN�f\&A�����8�kQY�[D{�n����Z��ܵ����X�d�v��DC&C�IJ`�fH�nSɴ]����jhpEr�tW](II��B���m�u#c��]&Z��֨�T/���.�Eg1����B_[ZS]
,PR�����aw⨇�ͷtz�-Y�vA�nS��a5L����һ��T:�}`�L���6��؍n���2L��Du���nrڳ�5@��c6�P���c��|J�z�Q
��y�I+Z���Z�[�,i�b�eq��&�V�ȑNe���jB>�o0���ʴ�����#�G�y�n3�!��!����2��l�1�$�l�z��������[:�A!Wa�p��-'e7s��\R=����ڷT:�v�2������!2�H�+2�cͪku�%Sc\���T�~�=������ߺ��p`Zo8`:�wd�_�U�ș$�!ֿ��P�l�	j��,��	�W��b��+]&O�=K��F���9�#�:$:\���"Pg�4���y]7t�M�����4��lr� [=.)�X4ja�V�yfx\u��H�wI3!�$+��9�v0h�f@�0匴�Y���i� _7�ւ9����()�\i6�N��G��BY'X���shq��\�4;�D��c����.��Mb�3�����K�/4�5P	&�v�}L�9������U��AA1��6������`"-�I<?�i%��0��/0�����2�k ˕V?5���m��nC��b�,Z7i�~V���v�0�D{8Z0����t�F2r7F��h"
���ƙ5�H%qd%u�(��v`��� �A>��n"5�$�H,�\0�aLG�v����M"�1��{^���N:1�7�
͉p�++��H?`K����e�̻�@2G蘤��rf�b]
SV][S�@ f
��zFMԔ hbD�B\Yi�&�c������������<�ZR[����H���Kb��k+�ZI�t�\�IhrmU	��^Y!mI��B[�YW�)�!F��YEkݍ��q�WOZ��8�nE�M/&�O�*ΊXò��(��";N��͝�Ϩa�1r�ҜٳjuŴ�aIC�W�P[SQ��j��X�S[�.�-����D�MS�J��gf�J�]�+��*�c*a��RgCw�@�fa�y�MZm0�	Y0d(�7{z.-^I1-y��F���H����V��3�ҺT�u%9�1.+�545�v�6�o��xl�ԥ
�PS� �5VB�7��?�nͧ47��5�fG����8Q穛��8�J��@m���DW�+R�k�e��eu�0=�P�,VWF���QU
J����T~P��>�/�@�>I��e7#.�3����6��x�$���9�9f]�Ś޾5R/,��ٌ�U��Ŭ�,��"��@
^�h[��X㖢��Ϥ%�n\�I�x+���%�!���Ru�������#'u��M���MMPG#u�$�
@n!L�M�
=�̪s8p̈�V	r�jO]���ns;�V+N@0�r�{�ݹ�ˀY}*�<O��b�E�5j)�k��23�|�^��bb+48���lr��j��=9�b�]q>#��	γ�d�]i����.6�-�C�Cb��>(��4�j��lNYTt���MEJ�MVK�ō�a�~��<�:S5�Q�x��N���26�)��-�	}�ׅ��`2�Xtp�)�%*\\Vr�		�}�[ml\i��o'C��b�� �8����`wZ`\� ^,�I&p�JHjr6��g��i_��e1rU�b3��F��@|j$qu�	}�ϧ��Ŷ'*�,ܰ�L0�9��#
�<@�>����p7 �x� ���9��Nϕf �')�C���

����g �(��Mg�=�B����7��,�m��2���Z�M}Q��:��:,M��fg_�F���"�I$��C�Up�$���LKb�:�ɤO\��M\^*�5'���Ɂ��B�I/K�yV��$m���^�tJ�(Mh��c�����V �a�X� ��a�Gb��������8��1P��5@m��7@��M�
�R�����Y3�2�O�m�7bm�?�C�����`�JV��U�D��1Xi�`S�Qu`�6�d�Ұ*�s�n�X�֏���+��_n��vC���r�@���} ���(,���D���I�;`ښ!GPOI��쿊i��+r)8��lh�X��O�x_���b�x���9��#RX$F@�\�'.!�`8�aL�p�R`�Ez�DD.cp���,6�<�S)&˄�h�	QX�HN��
ΈڼT��q`ε3�6U����J�����+5�1:/�#V���۠N���X���Ѝ�GI��+�z\�&F?��JǶ��.���q��h�P?����������eo����f���F0N�y �%n_dk�\�hrX��t���n�����y>g�d�E�M<y��T����!���
w�.$z���˅'��
�$.$��>��
௷^ �t%,����t���=����z]��]�DO=��G����$�L�v�g.�[�<�Kor
j��׉�\�rk�:ܞ�3(A�x!_���(yLQ|X�eh6�82�+���<��ƛu��T��*#��X=�|��A�UTj�����A��b��Ż�A��� �@�w���dP��������a\踈�:�F\�9w0a�~��oFZ�L�A��b�l���F�ņ���t��\�'1�F��|%�7�J��6*�Է�e2>uL.�3lz��n��nPWR},"Y�fr.;����+?MG|��������>�n�0�߄.Z�|�������;��N�x�]���K���������S��Pe��K�#���n]D]W
��٫������[V�]���m���5��߫b�E��������p�ʾ�W@�&�8&�����x��������:�x3��=P��SȻIR�� G1������9J{_RGQ�����}���hK��%��_?�z{�<'�k��7�<��k����	@@
З�a��p�}���5 � 6�t ���������~�[��!�g ^x�C�H���7R|
�`
�q;<nf%�&܇�Pr���IC|S����j��0��%d�����x�C���E.�F[#�2MD^(V7k�ɝydP|��ap�hƄ�%��W������	����~�>[{�i1�h�D�&�D��[�\x���z������Z�΍�C4=6+gw��}}��CM0ne���ȭ4a*!IT��l��0=�3P�b�#����"��e#�/ �A�k������7|�c@/��c�&�=X���x| SHɎ<�j�Mq@y���h:|F�h��ox7�n�\���:&�Q���ə%}Y��B+�rj����Scr���e)
�`� *�	0\ � �� �T�QÆ�?�h���6
��q9�Lf	�yl�&���J������ұ�
o�r3���Ē	�}I8�(� ��p8��/�S ���7�KiR��� ��÷�Iܒ8�BgHh�q�=7���o�����<�7����@\�$�2�7�����6���h������7�>��[ �LB�ϓ>�<�)�w,�
��k���ΐ�cW�j�����`�B�5R������VV6��Ƀ-��\�E���O�_+�Q��Y[K�qZK���1�|�&��q��t�qE�Tf�`�$���2A>�c^�?�R���ưļ*=+KX���5�T4]neI�b�
�xk�l�����V�6�ܵ6S�[Z�A�&C�Q���翷���� ^ �� ���n� @=�M � % �fd L0�8a
�<�� 9
 � � � �p)�% #� ����I�n��!�4�� ~ ������v��,�� 6 �	�0	`�p �D#�#�� � �`�� �<	����K ��X��
��� ^��s*��3���(�;Z�C�{9�P�.��0��a@�>)@�>��4Á>�� �!n"��`.e>QL�ХL@~+Я`n%x-|�Bxt3S�|��xS�'���dH5�?W$|-s9�b�.g���
f�'��Z�q�^�1q�q�:f<�����~�8��_~���9�$H5	~��I@G�R����{3����Rnc(l̆������w2��_�)L*|�~9�R�4���"
��8��Hcd��=�H?���0̓��ț(����>�s��U~/|~������I?cc>o�0�Cq�������ߒ=��!�G�#�8�Y�ifޒ�Tb�d�4��q�G�>o�/V�C�(�|����/�oȥ�N� O����?��4�e�����2K�g��|7��+���W!�~v�~q��
�lٗ�+�_�S���!1���/�_��!2����B����q�a1�=$M�r�L�����|��{�4~d�yb��eIS�YJi���E	���%�+�ɲ�ɖ�r�9I�X�[�C��)�sX�*�ҍK��Q^	q� �ay��ky�\;>�.�8�S��)S�Ay��K.��E�!�E&�A^p�"�gȏʏ�Gk܇W"��2=@�2C^����-�����U�G���eq�?�M��IV�2٥I�'�%i�������O�|*ᩗa��$L#�7�}I�I��$�[�dH�S)�7�}c>|�ҬU6��U^�4/� ��xk�G��m��K���>-I(�K���M*L*�$i�=�<�%�eE��)�ޤ_'Ic=	�MI���N������{�IQtߧB�����2� A@��E2�� Q	�$gXX�$'� ���%ɂD%	��(�` �
�w��w�zy|��������TU�9U]]�{�T�f3���������#�~d[�V0U{�F"UY��2�(�R�Hֲ9l"����D��`��4:���s�
��-`w�Z6���U6fRa�FWa}���l;�U����q��2���=;���xS���G�3{Ȏ��|=9��c��ٗ\��J.�h��l�����[xu������F~�Ρ�>����D��tr�U�kx�
W�#�E��2��j���r�v fc���h�Y�2���,By����RU;���K7ظ��{�X�����2�w�]�ez���}Q\���}������}&ʨ��Te�����;�tޝ��HO>���+�cT��q�D���q"�<`=yA��)=I��X�d�&��to�_㪞E0���6�
i�O�\���S�
cT�`<����S���?�#xV������t>�b��=\�I�����%���C���Z��v��>6�
ө�m�6F����"QP�y����"��T�~�m�c.V��bc��W{_[��B]�%�P+��j����r�m�6GkHE��܅Ӫ�QMl�Ъ�J�4oB��.^��ЊrU�4�]�/ğ�Mi����K��f4�����x��7��<���[Lշ��U�Ӭ,kEA��.�D�j��"��~˾agQw��`��Qv�b7�l+�6
Q�:��Pn�Dv������n�.���'�T�����V��~���Tm.���5Ѧ�=f}�h�#�&�.�����6�Y�T11, T12, T13,
    T14, T15, T16, T17> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17) {
  return internal::ValueArray17<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,
      v11, v12, v13, v14, v15, v16, v17);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18>
internal::ValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6,
    T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18) {
  return internal::ValueArray18<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18>(v1, v2, v3, v4, v5, v6, v7, v8, v9,
      v10, v11, v12, v13, v14, v15, v16, v17, v18);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19>
internal::ValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5,
    T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14,
    T15 v15, T16 v16, T17 v17, T18 v18, T19 v19) {
  return internal::ValueArray19<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19>(v1, v2, v3, v4, v5, v6, v7, v8,
      v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20>
internal::ValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20> Values(T1 v1, T2 v2, T3 v3, T4 v4,
    T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13,
    T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20) {
  return internal::ValueArray20<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20>(v1, v2, v3, v4, v5, v6, v7,
      v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21>
internal::ValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21> Values(T1 v1, T2 v2, T3 v3, T4 v4,
    T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13,
    T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21) {
  return internal::ValueArray21<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21>(v1, v2, v3, v4, v5, v6,
      v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22>
internal::ValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22> Values(T1 v1, T2 v2, T3 v3,
    T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22) {
  return internal::ValueArray22<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22>(v1, v2, v3, v4,
      v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19,
      v20, v21, v22);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23>
internal::ValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23> Values(T1 v1, T2 v2,
    T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22, T23 v23) {
  return internal::ValueArray23<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23>(v1, v2, v3,
      v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19,
      v20, v21, v22, v23);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24>
internal::ValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24> Values(T1 v1, T2 v2,
    T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11, T12 v12,
    T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19, T20 v20,
    T21 v21, T22 v22, T23 v23, T24 v24) {
  return internal::ValueArray24<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24>(v1, v2,
      v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18,
      v19, v20, v21, v22, v23, v24);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25>
internal::ValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25> Values(T1 v1,
    T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9, T10 v10, T11 v11,
    T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17, T18 v18, T19 v19,
    T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25) {
  return internal::ValueArray25<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25>(v1,
      v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17,
      v18, v19, v20, v21, v22, v23, v24, v25);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26>
internal::ValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
    T26> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26) {
  return internal::ValueArray26<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15,
      v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27>
internal::ValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
    T27> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27) {
  return internal::ValueArray27<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14,
      v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28>
internal::ValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27,
    T28> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27, T28 v28) {
  return internal::ValueArray28<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13,
      v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27,
      v28);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29>
internal::ValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8, T9 v9,
    T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16, T17 v17,
    T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24, T25 v25,
    T26 v26, T27 v27, T28 v28, T29 v29) {
  return internal::ValueArray29<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12,
      v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26,
      v27, v28, v29);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30>
internal::ValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7, T8 v8,
    T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15, T16 v16,
    T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23, T24 v24,
    T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30) {
  return internal::ValueArray30<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11,
      v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25,
      v26, v27, v28, v29, v30);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31>
internal::ValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30, T31> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23,
    T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31) {
  return internal::ValueArray31<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30, T31>(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10,
      v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24,
      v25, v26, v27, v28, v29, v30, v31);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32>
internal::ValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
    T29, T30, T31, T32> Values(T1 v1, T2 v2, T3 v3, T4 v4, T5 v5, T6 v6, T7 v7,
    T8 v8, T9 v9, T10 v10, T11 v11, T12 v12, T13 v13, T14 v14, T15 v15,
    T16 v16, T17 v17, T18 v18, T19 v19, T20 v20, T21 v21, T22 v22, T23 v23,
    T24 v24, T25 v25, T26 v26, T27 v27, T28 v28, T29 v29, T30 v30, T31 v31,
    T32 v32) {
  return internal::ValueArray32<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
      T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
      T26, T27, T28, T29, T30, T31, T32>(v1, v2, v3, v4, v5, v6, v7, v8, v9,
      v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23,
      v24, v25, v26, v27, v28, v29, v30, v31, v32);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
    typename T6, typename T7, typename T8, typename T9, typename T10,
    typename T11, typename T12, typename T13, typename T14, typename T15,
    typename T16, typename T17, typename T18, typename T19, typename T20,
    typename T21, typename T22, typename T23, typename T24, typename T25,
    typename T26, typename T27, typename T28, typename T29, typename T30,
    typename T31, typename T32, typename T33>
internal::ValueArray33<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
    T14, T15, T16, T1�e˖-_���[)~�V}l�V�o͚��[�~�'�����o�M���Z��O��yQ(f��� ��{�+���� ���P��O���>����p3.�q������02��˂���x�Q D^K�n�W�Cd}M������Ar^�2���٣q�Q4QZ�/8
�X��ŨW�*r��Xc���Bd.C7,�C�#��g��4�sS�Q�)��6�e��"j) �e, �`=| 6�QI��m�v�g��z��������2�'YIY���
P���Jx-z�bO/��c����\�s��?���DOg���A�^,��}����ؿ���_�4��)ʨ_�,"����/NF1�ǘ�1?�Ȫ�"T��P^���Qm�u�ԇ�k�
��	SY�^�6��}���p�#��pm�ÖS���{n�p���6r{�5�Ј���}�"�h�K���נ"�4\�V��k��x�9o�jyv�w���FtVx.�pEjP(<ߴ9b�_e�2�� �2DkE+��˚�Gn`�_���DG*>����GG����c��	��z ���ʸ�;�1.wl�'K|�l�sx}�@0�3W�<O�͗���~�H�bş~���J�L*�\�y�Q	"U_�V����ָ�8��hi��w�G��ݺ�H��+�wZ����7��O<��#Q��@Y-��0���]V?"O��P���G��b>_͜>n���J^�}%�.��ݍh��i�(�z��p:��w!b9N�te�7#�_8���9���u=��W�_���#�����[E�ų�%괒w��u=r��B_�_�+��3�ȋ�r̐��t:fl�B��l�
�����R� 0,Y�z'w`?���i��4�.�{ע<��8L�� �Ez�p8,��ӊr ;�M�^`
8�� {���P.` ��p�����
�`�� ����z�'���>0��������'���nB�Hz��N������~� p8LlA?&��W�^�Q�i`0� ���;p�܁�@o�K�����P_�n`7p�L��I���LmG{ KE��Q��$0��z�	�,����L ��!<������$�D��Ey�A�w�%|�&�}���"^`���:����s��n`�l���ϣ<��/!\1ڡ���`ɗ�߀)`������_E��n�0�5������L<�|���?`�y��~��A�|�K��psQN`)������O��z�� �L�8���\����L��r܈����A���v�;��zKP�WQ^`���ρ	`/0 v��~�I`�	���#��������,���͈g�-��h�[�ϷP�A���9	���G�{�9�x���.E���� ���wP^`��(o��#��	�a>/C>΂L�
� ����(70�� ��q`�J�f���ă��^�E�D;��r�}��:�/���؉��B}�ψv��n�������@�"��S�0
��$0	l��i� ��_�^��n�c1�}� v��A���a`�H' �����=hg�?�t����Q�G���	�w��Ɓ%���@/��40@620�u����3���2��N�/�>�����/���߂�L[̢�R���o�n���̚i���tu}oT�jY�߈����9�˄����iH�PB"��S)��> �2�x�=Y�k�WgW-�[M����tBkh�L�R�D`��B;B�hǔ�(�65"
�'�A�D^�Lx�dv��n���ZG�x�OL�*_Ɏ&�O�h��/�JQZ����Ǩ�����vx����.O��,(E���SC�d۴jѧx.t�DIH�PfI!��:>���^��zl�U�/"�ݞK������D��Jt�W ɫ�E����\=X+�1q~â�3��Ϯ���G�i�~�i��	���N�',�;���M��&����=Z�
��Qͺ�M}�8���Q��7۔{�W��H�ޚ����_� �]�aٳBz:Կ�;��?�c�e�~F�)fw�J�[��b-��;O��-��}�r$O�*�Eڠk��J�t��v�{�5�2a�E��K=���g2���̅X��<��Z�.�;>Y���m�o�ب����C���w�wE� |�/G�����*�tVp%,���u�H�D���������!�򰩑�P���W����k�?)_���Rj	k�MQ�R�ݢCA�A�?�{�		�T��с��POPeHmy}��X0�[��������3���뱓ʿ��q[����'+0do�֩��ƫy�m��e�m@�!�;j�pU�����C���QmV���E��Wi/=��q��(�K��j/�����e����E�m6����O?ՋVe���U�o�2�5"�4�m@<��0��bQ�,�Y��^:����[��COB�w)��
r��������[�=�R`�*1��`��J
��x���|n<���H��u�w�������2=9U�nͪ�Ն�������Tm��/&���x��3�d����rOv?�`ֽ��O8�Gnȧj&֫�(PaR��"Ej{>:�9���&J*�h=��Yh��iw����H���
�D�	�	ߑ'�5��=�t����n3��S�Z�g�6)�e�iP�n�5w�h��'"Ƽ��,T�=�qWi�'z���yU~�ע)���џ���?����U�Yv��f7��3v�,<��jg9��[i�|��'=�@_����fT���P�f�<��>؃�~ĳ�=���&Փs�V>)��1���L������|U{R�����G����Wbb@i��u!��Y��Ě�U���'�L=A�/<��S�|U�����=�y"�}��EG(.�BK�0�Bz��B���Z̝'�L�]D����o=W��߮�/j6]�j}9��4�<��%XC,��L���?�����=j��j1��pg�6�n1����r`��͖㈯�U���3���,К3����bpf�¿4�
&�g1�v����t׋!�b`%�6���[�� �	����E�ӗQ,+�\�y���(�'�Tm�>7�_dو[d.�*1WakE�2*w�;�x~�Lb��� ��wJF��"�Zv/��S����~����wG�_�"{����/u��/^q�睯ǿݱ�4� ���My��H�p1�'+��f�M�8�k� ����f�����Gg�p�l���XYk�>�+
>	~��og�/��F���}U��U�.k6ˤ��G����~���/p���䏃?��\���a����+X�j-�Ӹ�J�Z����eHV�_r�#\�nt�o����Owg��VK[�XVRܞ���C<�jUk�~g���]�[]y���8{X��e���w!�E�w���f�����/�`Mv�7^���q����;/���8���Kk��� �/p�G9~'��s��/�H����3��P��������]�Q�2\���e8O��D�rys]Z��>�w�T�gY��s�c!u�e���?���^�oF�|��s������ܶ����/�B�"�'����5f׮��,����#\a��պs�1��
�3�����U��Y��ԛ�5CQ���'(�Y�[y�G���z�1c��֋QqU�Ӟ��.sNR��X�k�e{��f��Eq�����#�l���a�]����<���S���X�e���c��n������ĝ����W8׿t'|*����^)��R|��p~�������|S� -+����r�O���������s����~��uq�nhԒp�e�F
�	/�/� �Z�v`��פ�������g6�}���D, ��_į<XLD�~����;�8_y��}v�'˳�zn�t����?�YRr�#kTm�Yoa�=�r��6_�j����;�W��wк��Awv��|e�Os����u����/Z�j¹�\g����Pg��Ә���/���t��^ԧw�➇����)�?K���ߙ����<�%��ތ�a�n��y��Ү����͔w
w�M��U�y�n&������h��p�nx����p5����iW�w�>ZA+U:[C��O�8|4�T��2��&�5F���KL��*��/�*�~|Xվ����QR#J�EI�(n��Y	�<�18hS��Z�V��*����A�
��ݱ$s��#��n�VIGh�-�9����_�6U�w6��4��Dͳ�F0c,�����j}��(��׏p�k�}��u��5�ٔ�������%����ڡA�Ý��o%��ڡ�ڡ�h��|V��Y޿�u5����vv�{�*�"Y�fpKV1��.A<��vx�8�]=d���q�
zm�5������;֜���a���>�ݱX�[�z�6ý�*ȿ���LA�da���_ܭj����"�s���+�$���"�z�3l?�C�_����g��C�o�t]1�hbG���d��ѱ_��3�R]�Cw�Ɏ���q�rQ�N��>anңZ�WH��������lօW�����F�槄�J����i��z��쫯MR�-�j��V*��
�z��`��)�����ʌVIo���[Sf*�2����X���sL>���w��*#Y.�����(�~W'�?&�����g�8��=�r6X�_��(���u�����<*��EqBf�vYJ����Ԣ��~W�g�\��^U��o�'h�5j쫘�Y����X�`zZ`��|�Ɵ뙎�9@mވ<
���Y&����ʤ�	����[�$�3f�nm#����/��ߕ	�ۑ��ѝs���N8Ds�Q�u92A;�d�G�C�`�,�N
��ٷK,�-���|۟�_�z�C�([r��r��z����Mxi�Q��5�x����ky����/���݀�.���N_LMS����=��蠪�E�~�+U�n��p�#k��2	��]�n��vv�b[�I;y�(�D��X��On5����y������K���2������=��+����c�=����	{�U�{��:Z퓧~e�%nk���G	�WU��n���ZZE��g��D��|+���pI�8��3�Z�μ�ӆ�߇=�v��T��t�jt�E/����%�}3�_�������O�(���Z�e�z��닆d��w���:{\}X�T��By����yv��N^�x�_�:ڣ�#��Ϩ?�p�����&��[=%�������<�~)���yA�? ���f�ǟ����8:rm0����>>��|���i���N�B�>����bN�U�;�瘿V�ɳA�j�f��r=w ��R��ʵ~]n_����{�:�E>�DQ���[����������_��^+�G����r��iv�w��f�C۔6��&��=ʭ�&��ś�TS#�
�	��|���Fy30X�y��Cv���_���FzJm�k����w��p�����+%#��L��,4��%���������d�s�X�?,�����^�B<}o���K>1��;�\�������ϻ-���-�ߓ��Je��D^0��YA�7U�:�(!�W�����7��8��V����l�O���|���#��VD����_������5�{t��(�xٺq�����R��6߃^�;=�2�4�kH�u��V���������}�1��`�g��ϹE}���uY��'�t����P��8�6��'�~���~7�[�*��)�����\������Q�zG�yV�B���v%|
��}�����"�_�wL[>u�U��N�s@k؟�(bL��TW�n�fړ^*��ў����O丗Dw���F�q5���1�=}��z�y�������ݛ��K���4ܯ�����B����g����'����~b�~0�Щ�Yku?��)��˱R�#W�k����}8���f9f����3f�;�g����ސ�^�z˂1l��G��.�p�Y��
�%�Ӧ�w�fv�]�r���I�Y*B������(�y�1^��7���x�2ϩ#��1(��[i���]�h�j��?)��ǲ�{�r���~���_9��c���Aߤ��o�4�_i|�J߮���]����ޫ�0ϣ;_��ƴ�<��)w���G�΁�E�x��A�n�_�X&
���JxK�d\�.Ɉh���H��1��9��i���z�����wDE��W�+�.�
&�P��g�>�it˼-�?A`�Nğ�tLۖ#󑿦<��B����kט�F�j�e/9�"�h�(^,��|�P4�?Wb=5����Y�4���5�{c�^�!� ���]��zܹ����E�%)R墕�3O�@\��ܔ��S��Q��L^NZ���q~����G>Z�˾�K߈�G\�~�~���|_hF$�?�ӹ��BS/4��i��q�����d�ˡӂZytP�7�q����߾|��9~������{����?Z%�e�~N!��"�3(��=�N�oZ�i��M�k�򽶭�-���.��2yȟ��"TMN���H ���c��)�]�N��g��2���U��?4�-��wn�ݞ�'O��#��]�%�J`H~GG�?���1m�������q��^�|���术��o�]�=��1��)y�c�hz���c�m�������-?e��=�*Y��7Xu}tL�S�u�R��|)�vL�^ۂ\�?�'�����K�v*��j�o��|7�"�,?��6�]���|�|��}���{�o�w�np��ׂ�5�/n˞��?�����ͮ/��j?~i�s�r��P�������x����r�K�`�\Q5C�o�����1��-���ʑ�]�MC�k��q�1�} ��~��w���O�~�O�:�㫐��Y�e~�F�,Ւ������≗���id}Td��|{}P���Oە2_�����v���j�ﾃ{�8�Wn�O�������*�[9���)��Z�w���$���VT���d�a��ǴC��}曖r���0��q��7}�/�z8.
��
���0ͯ��e��6�e�v|�K={���]g~g~g~g~g~g~g~g~g~g~g~g~g~�����xr���x��5���)6~&˯2K�_���Jcyڽ:gI簜zHǂw��8�ϴ���^���h�_�ӛ�h��od���x'����5�"��2��/g�Fc��n�71�GO��9����e�y�s�����O����� 7�K!㇍z`�Ct����̇���X^ɘd~
��|�&��>��E����%���W
A��(C���0_�y�0�"�M��.���<�1-x�~��~y��\��\���mGO
�h`hc
�e1R�ʕ|�(��3V�
�{ ��
UM���o祾Rr^T���o���TʚUSӭ\�.��V2�-��&�r��
�7�8���oX8|����(�߀�w�;/�__���S|]������O��2���c���v{�/����
���Q~�Q�O��
,]��N)+��(W�t�ʕ�V
�KW,ʻ�d� ���.Y��J_�����<�Z�J�C���.~�Ļ`�R�,]�p��Т�J�?j�+-2��k��X��z�{��cmf�҇Z�d����G�/*��Ĭ����
%n�y�<�î�}��BE�J���k���%˼��,�AGW,Y��2�C��p/���%���M_��V���E�@�-xh���Q�&�d)L�E�$/Q���A�4�'�©1gp�²%+�o�E�<��-��)xPx�˻�����2|��rQ���/�uA6��xK+]�w���].y`Y�ari��%��~xţ	j|p���8�^�p��DL	��r�*]������������_�hiI7~�>/�\��e�V�\��2a��
�����\_��p>�����%�{�ES�K�JI���y.
M����S˷���o%�=��UV�3�m�X��d����G<�ײz*2_�암�1���T�2���v���'͕�I�I%��o�3�z~�t�L�B9$E���Y��C=��
��ͱz�1h�G^%�x=q �˫T�����X��3��<�xO�e����;{�;�Y�3�����mW��h�{�U�o��~
¼]H��Q��`�?�޿�2�~'�_ۙ"�����DٲW>��ˆʞ1*������׷n�'PL�_/+ƫ�P�/CMXw��0�����7u+ ,?\؟G�@;�D��K�J�~C�=��u�2�8O�G� M� |�Xe�뮂b�w���w����,�#�*�`

��>u��jkmk��5S�*@k
�����lN�w�S��B1����0���`�W���T�����ْfa�6��5XM��j�ɚX(U6�j��'�WD���o�`SNXd%l
(�*c�~�q�mȅR�cSr�b�.䳏�0�zς���쒻��>!'�~�?Zj�6��j1��j.���EşKJ,�Ku9��o�(gA��R��� ���8��>�A*�ÊuZ���z����n�B�a����S�#-p�-`� 0<��H!���h��xBF�%Yv{7]�z�Ӡ�a@��d*��:��m�o�J{/V�1"y�|��/{ �^�
��5��i�X��
D�5<����4h)Mo=Ot��qG<r[|����
ko.��-��4Y}G�/$�o�HU�J�y�6��&����|��@ДH�X�,���F�7Ə���tG�_<��v��? �G� ���q z�H���;�S6��0�Y����t���Ԟ��9����q�y��E�\R����WuR)X��l�kPĩ6���6���d�5-�,&��p!T2[�w�5�m��V۽���9�׏�L�z%Gؗ�6�Jha�'����������yߕԿIVM~	[������F�NzN�6�_���_��O��|��o�TQ�f̜>E��V�x;��ePHi�ί�,?�+�&��������ݧ�f<Qd9 ž0� ���S5QF��u4���`�dV��- ��[%2j��|4��Y��q�(b�Z�}����hY��r��.�y®~�=ѭ-%Eg�/��M��L~n��9	^s���"M�׭�66Arhɰ�Q�&�H���tA'v�n���Q�	�c�S�	E�w}� 'w;v��ԌGm�G��=,�Aw˷�A>���3��p9K�q�t�h��zP}5\V�ãM��QP}�	�P���3�C����������������
���x����Z�,�:��L�XA+���m���=�@t��ݑO���������C��-�*�}�TvT�޶D[��|Ţ��JׯP��X���e���+�/!
[+g���ڗM4݅��.�G��בw�����r�����N��#�VگVu6�������]��m������3�G��e��k����I���V^8�`�b"�d}�?���������
�B��&��c�M�m�n���-t��y��m�o��i�	�#�W�W�^h��0���E�J��G�z�E��z����$%���%����������7*y�=�Z��2�s��!��,��$��`-��kho���Y���T�'�eg�|Z�2�"-k����}����c�9W��U������bU�:QR%��'�](�Yua�
n���4Ǒ�m�����:P�q:����T�&�u�@���T���Մ����j;��m�Q{b��<LWZms�V��˔浹���i����<�AY�e��)�&�c
4�]�F���w��h�㝃\��bۥM�8�X+i�o���h�V�m�H����h�z��
+Q`���������T먋l����b?ݡ)6�Q=��Y���:â6@�Ñ��_��0t9*?��P�!�a���q}@�f��|эJt���&�z&�I�={umLVt�\J�`��`�hYW(�`��8-��IM�lY�:��1X[��A�{�&J�]���H�I���:����݅� B8�L�*R��b�iir:�����@п��+�
���/�'i�1���|",+��s\B!2�s��\P<��z��}XsLy`ƪ�+מ�OTh�vp�Oz��Ň&����c�n��m8r�۰�7	�U�I)���H5DHc�՜q�j�AY
z�̊v�c-ܗ����?[R�����S��*͹�e�EG _�l��w3�ӇEA(�2T��'k��k��d����:Y�>��g���՝8J�VV�5��h�	�$��1r:a
����0��߯g�B�h!� ��e叇�����&.�C�=��̴*m�ن�i�0Y��ټ�V����:Y�]������O͕��g��)��i��N��o������,�B
ٻ׳��)X�8�@������HX
0��ϫ�z�
/�[��@�h���W��	;�0:�缩����<�s�'���7�k<~r.���9���E�G�O��_��Ϝ#7h^,zU2�k9��m�x���Nb�l8_��I�:�MV�ە�����[
�`�-�s�g>��Ls�>C�1�rs�Pځ���,��Mځ�2؆1)�_�68s�ڜ���V�O��2|k��N[�|��z��<�llK,�!mP�c��J",~^^��!,F�.G�J��َ�^����D_M���sV��Ǆ����R�J��Ǿ1�-�L����7�+���hb��=�n�i��?�<jx���q�%��L�l�����/�;[�.��~�(�}/X�缕��a��N^�!b��c�_�M����,�n�'#��#
��ei�Y�t���Ǭ��5_(�@{b%y-�Ų�<����b���w*ZG-�`؁���t�1�,��ك;0��Eډx�;	�0V3�>
6U\�/�<ЈMr|�{��$"�={�|S�ۏ&��WlȐTs�Ļ��=�@��#h��s��#��ڞ�� 7@�Y�3U@wv5#�q�)7 �PwQ2�[��H�Ks�G
����%�XF���#y��`Z�<Iab�X���X�T#�lb���	U��F+�M�Y��鮼�u!�N��3]�.�|��q���<8_>E
|��Q/?n��G<���)�5��E�i�Y�<��W�ۗ��l��8���o�qTy�۱�ê�+ct�g������-��x`�[9�V"��CE9���ar��I,PdA��?_v�_v���F�s�m�z���_��;b5G#�I������7
Ԏh�.�f�#��������8�
yA��z/�� F���
�p�&N��ХX9�W��+z�$��T�������Da���X���T#��9x�]V�`��������X��z��cT�\�mz�V�R�f�!&X5���E��Jk��x D�#��"e�>$�]���Z��pKED�<�@r�3@�я"�%��7�D9�!�>rڭ"Ɨ��E����w�=s8S
L���N��I�J�� ��:j���ZfHFV�F��x��ֲ��	�R�g�0����/�*a]K�4�� �anM&bM�X�-�iE����G=�ɳ�_���_=+
��I�Z���2���s���<K�Me�^���[JHpya �-ad�s��h�^�F'�Q�#ӿT��#����خ�>��YIw�����#��e0����n-cZ^Ӥu�-��zV}�E~p�U�>�Ǫg�8ulK-�㖺��Yu�c�}�0���u��|%��!,���-a9w/�IS"�a
Ry��Vy�F[A�|>���<8� ���(�G~�1�P�u 뀀���\�>��bf�`Znm���T9VPQO\ugy��s��z�S=����9?��hZ.E�*X3�<�g KM$��0�A�pV��6�;˥3� u� v�_�N�b���*�ͬ�JWb �_#�׍��������B�dP/���6��a�a``��Y�L���	�������b�^MA��rr����-���������?��}�P6�����9���J�y!�1a4^��*���[I6�&�$�a�r�#�vk�I��m�Es�6�.�&W�>m�Z��IlsmE�+S����;��FN ��jgm�յ�
���m��x��q?���k?�߃��vM�gU�Ǉg�u�z!}��Ʀ/:G��X
�~Mc9�����
v��Cg�w�.Q��J4r�Z�Q,�?ʎ3L�N�%TXga�R,0)��j�jQb�Ɵ��\�2r����~�S�fU�pѫ�!�bA�?S֞�|���Q�� �7x�k�^$���Y\��������߷�br#��&�U���R��2.��ע,i������e��ꥥ��6:���������Ii>�xs�+a��=�&u:p��X�>
;	��~�I�����9��F��C��R�������2d�Ѭ�U�oJ�����l��&w,�1�Ns:G?`Փ-џ�2�R��8m�nC�Vܶ-�����  �ק�b�X6Hp�M!���6��F4{��0HOl�3��1�m���X�|V�|砘�4^��e<��&Ǌ���Ϊ3�ֵ�eU[�> ��\k��Kg�k���U�@�ZA�OA��y�s�XY��շ;�}�X�|g����� ��= /�a��l!���u�:�u@�-����s|^��m���^���gY����	v�s��bg`Q���F��YD�K�+�D��`�ׁ��0���K��k�G}"#�l2r��j��O|����GG�ad ��8�p��Sm҆W�w�Hg`8�C�.x#T��[Lt�F���� ��&��>C��M+b�rUO�(�����k�ۖ��
�n���Z��3���[�3h��h��W�8�!��6
�ɠ]� ����v��,]�2J���ԣ��J��Y�i,���P�9K����p�bu"����6w�k۱S�~���)�
y��@�p�'���N�|�\T�t�����ħ�>���W��^L :`��%`�4�j�����os��wp9��k��^
�����Q�R�	��:G
`ƿ�LZ��x>"��*(M�e_B+ ��+�3qOn�>�ir�.tCW��a�@�\�[sٰ�LW��({J	��˝j�P��{w[��VJr��|9k��R��|���6Ԏ>����պ�
C<ڒ4��N�.3�qa�=�~�[���d�bzد����~��cRe>W��,��7\�բ.G����ê���cs���}�;���Z�㳐��&E=j��P�Z�QO�4�g[x�_����Z�Ԥ�8?c����Ď�-{�Yj�Â_�iV�m4���tLv����if"L�t���9��#DF.	�Zҋ�0�
k�w�;b���x��5�=:@�z/�ō<�Ϟ��O~xmy�W��Y�Tx��+�k��s�2�RҀ5E��^R�e���9��ōR�9^���x��'س�ӱ�{��	���C�<����+���O������J=����|� �U �7΅E	pS�7>�)��X2@����j	ã(pU�G^����v����NW����%�g�B=&�fm�-��f\&��	�:`h���`1�i){�H`��Qq�>�{Z�~���އ�o�G�E�hi�~̝Ú�����u��#Pu-k���Y枬~N"�"9a��n�����fDf�
C7B;���IY�u;�}�]�Ag�#B
�8(EX�n^3Qv�	<�&��S
Ξ�>ο���>�X��~>��q�h�a�Θ�+.��]N��yt�f3x�KƩ'�f����C\����Ȉ99��\HJ �3=z��p�p�(&8���Z��Y�@oN���&۫�����^�Q|	�SX�m���X�I����N��0�	�XLRb53;}�j��s�S8u6u����0P�eM�*R�*���T��V�l{���g-��lC+�,�V�{ɢ�>4�7-�|܏�x�����>KJ����AΧ���6����ՄI��L�3�V��zy�[�<E�:ՊOs(��IL�!���Њ1@=�U�w�f?��y-Z�OȖ��c��h�4�r���v�t���%�	��ڈ��@��ɹ��ڀ�5��O)\�B
��K�=B|!H=��Oқ�[�Ī3
����L1UB��$vK<��a�,G����#V~��pY���m���N���du�}��l�b�"Z-,X�U�kY�щ�C!��|B+��y7�{ceG���JZ�G��qF�Vʱ���u���^�R�&�jP�[�5�Ҫm�,�:V#������z]�?���{X_�> ���B�wZ�O����l�C�0�˸��_	��'̦E|�O��H���|d��M���a������]�,�k�~#&p�Nz����yV����U����-w����S�'�߇z�0Y�#�й�Q��J�8��'�9�����W;��0'�؜,Λ�]�Bӆ�_>åX5'�ɑ['�0�:1����1
ܱMl�?TL&d�a�PyƦ�=�^u��=����%=pc-�*�v1�l�
���0H�c�5�s9�s� �&����gU��'|�r��싻>`��w4��I
�,v�bO}>H�B˥���a�J�1�c9&�W��PnS�ɐ������++-^0��������6�`�q��6�T�������S(��Tϛ�
�T�n�վ��M���A�� Wk���H��70n�DiҲ.S:lL�JK�Ȃá�`�o 
�͖:+���q,�;~,��b��]���~��U�ϥ�:�:�7Z	#Ȩ����R��#>K�2�p��p��q����ߋ�n�O$I~0���y++�et��� �gj�O�����G�o�=< �������>[��ߴ�����J�	���k�h����y\EX��)������!|k1N�
�d(��ek��ӿk3U�F5�7���BՁ_zr��1ï����P ���,�x�"�s���?�G#�l�"W9I=(���󑃇'����N�{�䷺�ˤ|
��=;Iࡣԥ�v<�"�[�]/�kK����t�������	�Ҹ5"ȑ
tC�(�c1$m�9BړT)�"��H�F�m���:lE��8�j�a���cb"��R>��È�㰿7��/���݌�[y>�M��3��dW�hC��6ru Hz:�1�Z�(�ېQ���Y���,����͛X��;ڏ�w�4(m}�Q��M�C��D,�I���ͭ�L3
�O�v��Dڨ�.���t����	V�����+(P��)~ήa5�`�x��"��W����g�P�N*+F/k&�;V�p�r�q�<��8Ty�O}yG���
z�)�q��~|,�6FUc#Y�ّ��c�Af�B4S�<��1ys���@_r�x�F))�|�Q�G�w�0j��.�Ü�0|ɀ6�w��aF��T"�Z�?&xU&�.k�м��X�֑��o���L^���俲����l�7�Az�nXw��X�dh7���|�4�WS�)������ŭ�G:ɥ5�l��qx��,���OuU�u��l��<���rh���U?q2�ͣ:Ƕy�|P���Js�'���!�U����OP��
���P{g�m�HDB���T�q=,�ji�^��!�H��b��
�F6{��?𞍰^����(���+���1����8ow,�D�'fy�ND�Fm�"��Pۜn<t�lvj/��FMB;��4}���D�C1G)�����O���߂���X���\o�h�[��f0�@��rra���[�����E��3`��TѦ�����?2)œ��|�<?��m�7<.c�@$���)g���W��|g:�i�7��\���(I/��-����<)�ȇ��q0�(���;��FGy��Y��2���HO/ѫz+�ѭ�K��3�B97/p��$�L��kǕ��Yi�=�*CW�^w	`�ᢛ��U��Ƃ7��f��x�G�K��a�@�p�i���q���	�b+x�{1���o�qߜ�0lw�Ɩ)�3��s��?��dV=��
�NGF�r�
\���[����9� �����-��} �~��_�wc�}��μ�BK���U��A��}�vϓV~o����=��*k��R��� ��}_6y`]�ەR�S8��ι<+����I�G�t\t���=��6��8:��5�a�.�YJMR&w� ����;��@0z�̂[�BΖ�bh҆"֒��ux츟K	/�jy�@R��%'�M�\�6���G�⪃�KN�v
�n�0{A����K��X�5�o�"w���ڣ�a5��'�B%�E���LOn��E����z��@`�z�G�'�%ړ��h���[��ʝt�;�d��Rj���3��d�F<�&d����6��0�3Hr��ʍG������W�{�a�X���k�W��Tq����N��cHiuw�ᐑ-Jf��6�Z�oj��f�
� ^�Q.���k��o>BEw��
��m�ȡ�v��d�r��`R��8�|�0b>��P@�&b��Sq0��MHʧ ��vB	����ӭ�m��_"�
��@cS�w���8/��;�P8���+�@ߤ�<�%_<�+�����s��r����c�gm��\��p��?�x|�����];r�Iu��%[�M����
�χi����P<]X�,��.H��i�.�����\Z��4n�|]�i-x>.�0��p���:��A[䵰9�94�o򨭲
�5�V�3¸�8/|KQ�����0,Hs���X_�p��3BZ(8L��8��Qy$���x��NAWY�C���gzO�P��.X�N:����D��R�g/�hsg
�4<p縉y�z���[[i�|
��`�N�<�U�{�ً��߇#B��]��Kj���z�1����}c;��ȗA���nd�P�I(�UGɛ�lsx\�jc[��a�a%�pv�7�z����et���Jʗ=
��W*1��Y�-����`̗k�f{u�s���2����:��c;�h����?DTC)Nӕǝ�碟�O<��
���Ќ��;�B�"��!+_��s#NK�'w��
φ��I��tX�
-E�kx����v��g¢� ��؞d��Vtk�p>X�d�|�c�� �I��G@U+\��R��*���+IꆹhUG�b��X
Å��Mu
��hz<]�30#iO�G�F�5�W ��q�Ԫ�����]�*�๩�苊�eJ5�����X�x�#��ݖ�ܲ2��T��4���v�-���[m�2!� ^JD-M��9�I^��y��=g� �������+g��<��>�s({����B)��	Ŝ}
����յ�Ҧ4�|��"�~�X�����ڼn������z��bz�05�#��_�p��£b	G38h�Q�x��tg��T�e
fy����1��DSG�R�0E���46�%��ݘ���ZL���ƌuO&�[��v���J��$@���w�ǝ�q,X|��]�b
�4��.�JrC���:�)���~�bgqH;М�|�0�6L2�t��U��A`�^(a�@}%�]d���W,��W1̻�����7|p����$_c^o�H��̷�WS\��q@*��P]�n�4M���[��Cw|lּ����X�J
���υ!w�i3U5�������s�PP�zI��C_�M�/ "�95�R�\��dwYU3���hz�\�t�^��E��'h��^��X��m(�-���
��&�q[�y3w��-���C��ׄ��3�w�_����:_�]�Ȗ��*���9��8�����+���#眸Cm0����يH/�Az�LP/U)����i#��A��������G�W��e�F������������h�㟨|������T�9a��(���T��y�ZVgb����4_F�bL��}t]rrj�b,����^*) ]�Xq��f�e[f�����I�Vy��c�܆<#g��f�V�=y�6ʙ�њ���y��
X������Hr��X�b>0,�~�y|k�|w�d�y�!�l�d�]�������s��#?���O�-�9��濢w�B��t|�K�9��K���R��H����cF�:��/��忛��]�;�c�b��� ��X�:>�Hw�l�9HD6��Y�dTͧ^w֓���8Z�(��^E�0U���c���{&V�/�|"�	|y?��_�;�1n_2��Bq/��a��Q���$>u�:;,���vO��)7HrE�j���1��W���fF���`P���Y�~}2������1AZ�;�����B6-�Q�E��6�rM/t��I��)Y�w#�I�0�":�EfK)�0����!k/>���^� �K1z� �?c��Јg�;�-Ud �W�������w�"���\�I�rK)��C�D��w����i+?��t�k�.pU"�!�r�}E��E-��7��ᜑAՍ�ݟ(=����\����	��2�����@�CL�qB���T$�ȸX�Pi~G�;.{��BI�e�4`�־K��^���-3+�����V�aS��<�?�w<hQ~����vl��S�m���4
ί g:��|Ǚ������չ�L�����ޛ7�����+���2}����x�o'P5}N��Q����em�?
5/�L�OPT����|I��^�u:�KDZ�$��S؝B;�f���>ӹD������-��"ԴP�Y��?����oW!�Ӊ����%��!�+�sQ���"6�u� �#R����B����Q�l��}P#�Ǭ�Q��9���@�t�����nN���C���+Mⱒ����)O2I�{c�o,���1��M���)/�ʉ�4l�1�lp��Y���W�{#)�ʜ9i:��O���o)P�ws��xg�nR=�UO�(Y�\��E�#m1��N�w�v7j��[<���W�>�w��sc��V�����`������.r��$x�P�_�ŀ��"��Z*e���Fk�U(p)x����
%>�Ť��p��&�u�#��G����ٲx��IjV������X����&TJ*H���	�`��G�r��K
��Q���W:���A�%#�%��r:\d��i�'��ҿ�f������]�"s���\e)s=5�P]�d�̓��5�;���J��%O+�x{�o7)XgYX�,�`���2<l�po�G��4����j���&��
N��`(>�8P�EXDA�ɤd���ޓ6.Y
0�9r=����Ksr,R��a���hl<�����=�l��{��x�C�9��^c�w�+�?�YG�2NG�p�E�"�*�E�7�7��S���d�� V��6��{��ګ�b���%��}��g����$�3���tZ��^�5��L*��<f��un?�@`�E-�"����������@��`� ǰ�8�a����L�'�[/`������ȼ�t�
�)_���O�h��m�ٕt�_ଌ"��62�<�#�5�)+�-��E.��˅Z��#<�_<p#���ۻE;"-W_ZB��P�U�<n����<#獑�L�P�� �!!��U�����r;�|=�����E�N�E
xUJ�-f3U7�:������%f�J*h�+e��g���Y����b���r��� �}'	N�~�p�)�B/���7�ھ#3j���'!߫p���?�
3�=�z���:�&����Ͱ�G|g�M�V3��7��q
����kuKb1�Q�o!���шglI?c���	�M��tN͓��x��Мx�����w������ю�(�Y��B[���>ؒh�u_η���#г���C��pj�:A�A�����ѯ��F��+���{z6)ę��itdc��rU�������
�$��I��m�x�݁�\{ ���
�8ԡ�E<&Vŋ��(?�U~����Dk�j^����GE�l�f@���8��,�f�إ��e�u�
��^{�K� ay�[�}V��(�
��+ �;��z��x��#�1a�H��j��	oH��i_����̌�g���8ݕ�-o�qG`&ot�pP(�"����Y9�v�x���|��PV ߄�$Y�����Ѝ��Q�wv.��=i]��E�,�|��@ڵ)�.�:s�}��X�s��Q0�ֲ�������G�}y�e�1)��³�s���!e����C�%tAl� �߀ыf��F�\�4U��X�N��D?a������$�����p�H)���	?+�ء�&�Ve{e �ث�HVX�1 s�B�*]DDO�)�7܀n���+R'l��.�pKt�f�zF����+FEU<6�\�4��S9V�YNԗ�&U�W?�Gne$���T��s����C7>�?B��yS}O<��ǀ�͹ro���b,��c�d�={�� �J�V��vO@�Nb�{$c-��[�0w�<h�x�g7�m��/b�Cނ�G�C�-ᚲ�(��b�7�0���{�-<d
�h| [�E3�R��AA(L2Z���ȟ ՟@�G5����y�w��\,	�4���	�Q�k�߷�ӎy'��#����7���l�ϼ�	���V�,27zQM���9hd�A���1/.��ld��&�¯���3��b��(��C]��v�ń:�2��S��J���GW���:�VY��p������S�N��~A�|R�ej<��<���)�+d�8��<nv�{��gXHI���Nb0���aN��ĊD1�\[��2�s(A�	��}$!A������i�YmD�l��cp�z(L�A ��ǈ���x"l��=C����Qn�E`�<x����cp�~$��(~���"��NQ[�-��f����@�3(^��l�$ ��ܮ{Ձ-�8�@����7� ��3<���Ժ���x4ǣ%�$��C2���b���=2 ���=�r����o�$}��s��X0g2�7�5Z�T]nP��p��<��X)����"�h�-*Z��t�=�I��x�ِ�%�zUB�\[���c}M.JIs~�K���4��ա9�� '��,���/��b�/�E�E(Fu'i�N���mO��i���oV֚�����sG�k`EYƳ��Ί�y��՘�=�J�G��}1�a5:^�w��a���V{v�7������w
�
��Q�irR�z��.����Zg�e����d�:3�[ax3]�����ʊ'�(�
/=�<�����/�դ�/b�T��cب���D4��~�����w��s���|t��$ O��1�
Iv6���m�G�{/��+��[YQ&/)Њ�ԌA��Pz���e	��;F-H,S�nZ��\���)풋ŰN�&
̿�x���+:�F��*:/|�u/y�����&7P>Њ��������J�P�x��SK8��$>�Jq�Oԫv�g&��祂c1W��;<J%ߔD*y��T-$
�1��E�$�f:�2r�G���u���rC�u��)'#&�/�?6IUA9ccRN"�	.(�VN�{D��tW �(��ኗ�^-�-8��lX�kC�Q�_��>�����<��f<�@l��i�V��MFj�SjB�4���rE�(G��ȴp{By��|7�MT�M�<�,b;���O��F{`J�n�Z���x���c�MiB���=��G���.�hj)Ͽ0�������N��Y�����
�)���N܅k��z aa����$7K��������F7���#W�����H��CM��O�m���Dt����D��#��<ȼad��#FWJ4�)�d���� ���=�,���~�Y��8X�)-�J�I89�I/.ƍ��G�K�j����ElIΒw�!a6
|���h�I~t������\B6�N���'����$�0cIJiBݠZ`]n��*�.���$e,wcT�,�f���x'kH�ʋ���L�4��N��
�HT	�V9{(+���l|�ș���^�}�g_w��d�hb�P��qn��y����ґ��U�Y
X���D������{~`R��&N0;	���P��I�2�#��N��s-�����ph�m�|In�`م���Y��9{�k��邝�j �N��R�p�;ID����5R_
y2@���:�2d��d���+��V�F�����8+%�_��'�5�&�V�H�8���e�c�䘰�L����~(�z�J��,���C�����8�)3�l�pΘ�y�I��V��i�In�����(<
N�9�~QqE)��	W�
 a��s	_]L�sLG�>)��Y*���ᶼ5��+���r8	t�X冔&н8�{�7�����Yr�g�9��r'��o��J&V���ܳc쵄�ۯl�[9=󝾕�d�O�:�s��������=��F$�졋�%<�]�>��ǥWI��<�Xy㼮^#�K.�K�bv����ĝ�X^U�ˑ4l��M�1+ͺ\��cN����}�D�i�����(��}QE��+��f�aY :I���b���Ǭn�\��=	}�x�%8�,��R;�(W�~?�s� �~�uf_G���JHp~O$<���T,p�gї3��u�����vʵ�b�z�.��#>Y�7rE6N��'�|=1�N�-�z5��_\s5�O��L�A����I����F����x��w!f�I�C�T�1���"[^6��}=![2��r�[�� nS��8�,��u:E�x2�]C�k�ɿ�'�_C��CN�Vp���YL��d8v��׈��k4�c��)#aU�[K0�&�ۖ�C��
Wm,̲`0hTn������3<�3�e�[]׃<x~�s�y��S�'܍m��;�T�����u��5|�
� k�&�t��"}d���!�Lף:v=űE�0=0�����]�q��8����w������@���4������ڋl���/6ښ>o2GlM�� P�W�7�9@e;�Z%�j�����4������N����.��0��q�r�4�a��X�h�K9��!�N�&�5��@v���NOƾ��q`������=�r�?gu��K�\h ��sp4Dp�<}$�\W8r�p� �= ~=��G�O�ut8�>��7\O�����g��H`�2�h����fK�=��|H��o�ɧ�Y'����T
��П)�O�����8mf�ï� =�
=����R4�\O�F5�k�hܐ� h7Ҹ�� ��{���%H���뢈�;�4!�E&��o�A�E` ��y��G5���yP�Ha"J��$��`�h�=�Ӵ�m�9���K��ŎQ��OX�k,��6�[�5��G/9�-ǹt�,��a@O�0�w��n�,}3L0���#wR���?;F�{i�p>�qA�%43�&~���"��?}H�F#�ӏ�N�Z/�`0��I�M�!�%�
�Fh�V��n�[�R��=��E:+Z�WL�1�h�qMtcO_�����֣ t�m�o�~ptC�/�еǸ4��{�ZM��Fg�Z8�M�+��������Sfr8�_�'�����pz�K,p�rT�Xa�udpin0S�R��h�T�K5��vZ�\)g�����u	!�;P�l���D��κ�>�K̫��ܪq�PϬp�u��0�l���v�M.��g�ۑh[,�Rm���O�9x)S��{f����E�����Xw/��df�s�st�H��Y�Q��>zN�т譽��X���"��S��I�`� R�042Y4����ZV���$� VXw�x�tw������'������Qʪ���MM��ļ��X�}���Q�+�yy����\��p�Sͺ�Q}���%�~K�;q�W\�R�����?܀3���xCT��K�:N�б���=���;-�3�9����S�F�3� �[�X�ћ�Ⱥ?yp5���E��5�|m԰>����<$<�PA�-�6��Z��!���H��\�$�Y�5�[TH�V�@dO˵u��@2�������7�o�q�v��# �y���F����-Q��t�qƄ�R�K'4}ً/:��&'��� ��� ��,=�/\�f�ɼO
�F��W�)��~>
�ۂ��h���{Zat�p;�gA��+,�C�ȁ�C��?[K��'�pk����rٯ�#����R�^S4k?�+V�oA����pX�����FO3��n8D�n\��vڞ���ž�܊Xp�w��'v��7p���=��zRhOZ�ߛ0�k�J&���|	�L��(�?��v��"�����C��~�x��g��V
jk�XD�>�
 ����ސ��N�!�*���YrE�(=A�.X/�8P/�
E��7��}�0g�z�H����Y����#O�+?�{��~�{���M�~�7� �֡��B�,��dB������R�z@KÐI;�a*3b��V�A�#là��j�@�9tMK]SH�ND�^s56�YM
m�����
�#A�L�h�O)��a;5����V�{��U�Y{���J�c�~P��ڒn�NNKmW4�0�T'��jZ��?k'���T���K��x���5�`t2���C1���Ei@~J42Od��yS��d�j��C��3�i���6����%W-�Z�j�\Ok7%�d}`��T#���*e�G�Cis�!�<���Vu���]y����w�<��E��L9�κ�������{��F�����%�cv��Ë��;t}oaE������EI�=>������s ?k"�����T�~��]��FL� ,����������^S����P��Q�'oR�Uu��!*jT�b�#�ч7���O��'��'A[%���?�[%�ɩ�qA��h�����7�B/���i�/ ���I2���w�

// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)

#ifndef GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// This header implements typed tests and type-parameterized tests.

// Typed (aka type-driven) tests repeat the same test for types in a
// list.  You must know which types you want to test with when writing
// typed tests. Here's how you do it:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class FooTest : public testing::Test {
 public:
  ...
  typedef std::list<T> List;
  static T shared_;
  T value_;
};

// Next, associate a list of types with the test case, which will be
// repeated for each type in the list.  The typedef is necessary for
// the macro to parse correctly.
typedef testing::Types<char, int, unsigned int> MyTypes;
TYPED_TEST_CASE(FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   TYPED_TEST_CASE(FooTest, int);

// Then, use TYPED_TEST() instead of TEST_F() to define as many typed
// tests for this test case as you want.
TYPED_TEST(FooTest, DoesBlah) {
  // Inside a test, refer to TypeParam to get the type parameter.
  // Since we are inside a derived class template, C++ requires use to
  // visit the members of FooTest via 'this'.
  TypeParam n = this->value_;

  // To visit static members of the fixture, add the TestFixture::
  // prefix.
  n += TestFixture::shared_;

  // To refer to typedefs in the fixture, add the "typename
  // TestFixture::" prefix.
  typename TestFixture::List values;
  values.push_back(n);
  ...
}

TYPED_TEST(FooTest, HasPropertyA) { ... }

#endif  // 0

// Type-parameterized tests are abstract test patterns parameterized
// by a type.  Compared with typed tests, type-parameterized tests
// allow you to define the test pattern without knowing what the type
// parameters are.  The defined pattern can be instantiated with
// different types any number of times, in any number of translation
// units.
//
// If you are designing an interface or concept, you can define a
// suite of type-parameterized tests to verify properties that any
// valid implementation of the interface/concept should have.  Then,
// each implementation can easily instantiate the test suite to verify
// that it conforms to the requirements, without having to write
// similar tests repeatedly.  Here's an example:

#if 0

// First, define a fixture class template.  It should be parameterized
// by a type.  Remember to derive it from testing::Test.
template <typename T>
class FooTest : public testing::Test {
  ...
};

// Next, declare that you will define a type-parameterized test case
// (the _P suffix is for "parameterized" or "pattern", whichever you
// prefer):
TYPED_TEST_CASE_P(FooTest);

// Then, use TYPED_TEST_P() to define as many type-parameterized tests
// for this type-parameterized test case as you want.
TYPED_TEST_P(FooTest, DoesBlah) {
  // Inside a test, refer to TypeParam to get the type parameter.
  TypeParam n = 0;
  ...
}

TYPED_TEST_P(FooTest, HasPropertyA) { ... }

// Now the tricky part: you need to register all test patterns before
// you can instantiate them.  The first argument of the macro is the
// test case name; the rest are the names of the tests in this test
// case.
REGISTER_TYPED_TEST_CASE_P(FooTest,
                           DoesBlah, HasPropertyA);

// Finally, you are free to instantiate the pattern with the types you
// want.  If you put the above code in a header file, you can #include
// it in multiple C++ source files and instantiate it multiple times.
//
// To distinguish different instances of the pattern, the first
// argument to the INSTANTIATE_* macro is a prefix that will be added
// to the actual test case name.  Remember to pick unique prefixes for
// different instances.
typedef testing::Types<char, int, unsigned int> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, MyTypes);

// If the type list contains only one type, you can write that type
// directly without Types<...>:
//   INSTANTIATE_TYPED_TEST_CASE_P(My, FooTest, int);

#endif  // 0


// Implements typed tests.

#if GTEST_HAS_TYPED_TEST

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the typedef for the type parameters of the
// given test case.
#define GTEST_TYPE_PARAMS_(TestCaseName) gtest_type_params_##TestCaseName##_

// The 'Types' template argument below must have spaces around it
// since some compilers may choke on '>>' when passing a template
// instance (e.g. Types<int>)
#define TYPED_TEST_CASE(CaseName, Types) \
  typedef ::testing::internal::TypeList< Types >::type \
      GTEST_TYPE_PARAMS_(CaseName)

#define TYPED_TEST(CaseName, TestName) \
  template <typename gtest_TypeParam_> \
  class GTEST_TEST_CLASS_NAME_(CaseName, TestName) \
      : public CaseName<gtest_TypeParam_> { \
   private: \
    typedef CaseName<gtest_TypeParam_> TestFixture; \
    typedef gtest_TypeParam_ TypeParam; \
    virtual void TestBody(); \
  }; \
  bool gtest_##CaseName##_##TestName##_registered_ = \
      ::testing::internal::TypeParameterizedTest< \
          CaseName, \
          ::testing::internal::TemplateSel< \
              GTEST_TEST_CLASS_NAME_(CaseName, TestName)>, \
          GTEST_TYPE_PARAMS_(CaseName)>::Register(\
              "", #CaseName, #TestName, 0); \
  template <typename gtest_TypeParam_> \
  void GTEST_TEST_CLASS_NAME_(CaseName, TestName)<gtest_TypeParam_>::TestBody()

#endif  // GTEST_HAS_TYPED_TEST

// Implements type-parameterized tests.

#if GTEST_HAS_TYPED_TEST_P

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the namespace name that the type-parameterized tests for
// the given type-parameterized test case are defined in.  The exact
// name of the namespace is subject to change without notice.
#define GTEST_CASE_NAMESPACE_(TestCaseName) \
  gtest_case_##TestCaseName##_

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Expands to the name of the variable used to remember the names of
// the defined tests in the given test case.
#define GTEST_TYPED_TEST_CASE_P_STATE_(TestCaseName) \
  gtest_typed_test_case_p_state_##TestCaseName##_

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE DIRECTLY.
//
// Expands to the name of the variable used to remember the names of
// the registered tests in the given test case.
#define GTEST_REGISTERED_TEST_NAMES_(TestCaseName) \
  gtest_registered_test_names_##TestCaseName##_

// The variables defined in the type-parameterized test macros are
// static as typically these macros are used in a .h file that can be
// #included in multiple translation units linked together.
#define TYPED_TEST_CASE_P(CaseName) \
  static ::testing::internal::TypedTestCasePState \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName)

#define TYPED_TEST_P(CaseName, TestName) \
  namespace GTEST_CASE_NAMESPACE_(CaseName) { \
  template <typename gtest_TypeParam_> \
  class TestName : public CaseName<gtest_TypeParam_> { \
   private: \
    typedef CaseName<gtest_TypeParam_> TestFixture; \
    typedef gtest_TypeParam_ TypeParam; \
    virtual void TestBody(); \
  }; \
  static bool gtest_##TestName##_defined_ = \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName).AddTestName(\
          __FILE__, __LINE__, #CaseName, #TestName); \
  } \
  template <typename gtest_TypeParam_> \
  void GTEST_CASE_NAMESPACE_(CaseName)::TestName<gtest_TypeParam_>::TestBody()

/* JLBC: Disabled for MRPT due to "..." still raising C99 warnings in GCC (2010)
#define REGISTER_TYPED_TEST_CASE_P(CaseName, ...) \
  namespace GTEST_CASE_NAMESPACE_(CaseName) { \
  typedef ::testing::internal::Templates<__VA_ARGS__>::type gtest_AllTests_; \
  } \
  static const char* const GTEST_REGISTERED_TEST_NAMES_(CaseName) = \
      GTEST_TYPED_TEST_CASE_P_STATE_(CaseName).VerifyRegisteredTestNames(\
          __FILE__, __LINE__, #__VA_ARGS__)
*/

// The 'Types' template argument below must have spaces around it
// since some compilers may choke on '>>' when passing a template
// instance (e.g. Types<int>)
#define INSTANTIATE_TYPED_TEST_CASE_P(Prefix, CaseName, Types) \
  bool gtest_##Prefix##_##CaseName = \
      ::testing::internal::TypeParameterizedTestCase<CaseName, \
          GTEST_CASE_NAMESPACE_(CaseName)::gtest_AllTests_, \
          ::testing::internal::TypeList< Types >::type>::Register(\
              #Prefix, #CaseName, GTEST_REGISTERED_TEST_NAMES_(CaseName))

#endif  // GTEST_HAS_TYPED_TEST_P

#endif  // GTEST_INCLUDE_GTEST_GTEST_TYPED_TEST_H_

// Depending on the platform, different string classes are available.
// On Linux, in addition to ::std::string, Google also makes use of
// class ::string, which has the same interface as ::std::string, but
// has a different implementation.
//
// The user can define GTEST_HAS_GLOBAL_STRING to 1 to indicate that
// ::string is available AND is a distinct type to ::std::string, or
// define it to 0 to indicate otherwise.
//
// If the user's ::std::string and ::string are the same class due to
// aliasing, he should define GTEST_HAS_GLOBAL_STRING to 0.
//
// If the user doesn't define GTEST_HAS_GLOBAL_STRING, it is defined
// heuristically.

namespace testing {

// Declares the flags.

// This flag temporary enables the disabled tests.
GTEST_DECLARE_bool_(also_run_disabled_tests);

// This flag brings the debugger on an assertion failure.
GTEST_DECLARE_bool_(break_on_failure);

// This flag controls whether Google Test catches all test-thrown exceptions
// and logs them as failures.
GTEST_DECLARE_bool_(catch_exceptions);

// This flag enables using colors in terminal output. Available values are
// "yes" to enable colors, "no" (disable colors), or "auto" (the default)
// to let Google Test decide.
GTEST_DECLARE_string_(color);

// This flag sets up the filter to select by name using a glob pattern
// the tests to run. If the filter is not given all tests are executed.
GTEST_DECLARE_string_(filter);

// This flag causes the Google Test to list tests. None of the tests listed
// are actually run if the flag is provided.
GTEST_DECLARE_bool_(list_tests);

// This flag controls whether Google Test emits a detailed XML report to a file
// in addition to its normal textual output.
GTEST_DECLARE_string_(output);

// This flags control whether Google Test prints the elapsed time for each
// test.
GTEST_DECLARE_bool_(print_time);

// This flag specifies the random number seed.
GTEST_DECLARE_int32_(random_seed);

// This flag sets how many times the tests are repeated. The default value
// is 1. If the value is -1 the tests are repeating forever.
GTEST_DECLARE_int32_(repeat);

// This flag controls whether Google Test includes Google Test internal
// stack frames in failure stack traces.
GTEST_DECLARE_bool_(show_internal_stack_frames);

// When this flag is specified, tests' order is randomized on every iteration.
GTEST_DECLARE_bool_(shuffle);

// This flag specifies the maximum number of stack frames to be
// printed in a failure message.
GTEST_DECLARE_int32_(stack_trace_depth);

// When this flag is specified, a failed assertion will throw an
// exception if exceptions are enabled, or exit the program with a
// non-zero code otherwise.
GTEST_DECLARE_bool_(throw_on_failure);

// The upper limit for valid stack trace depths.
const int kMaxStackTraceDepth = 100;

namespace internal {

class AssertHelper;
class DefaultGlobalTestPartResultReporter;
class ExecDeathTest;
class NoExecDeathTest;
class FinalSuccessChecker;
class GTestFlagSaver;
class TestInfoImpl;
class TestResultAccessor;
class TestEventListenersAccessor;
class TestEventRepeater;
class WindowsDeathTest;
class UnitTestImpl* GetUnitTestImpl();
void ReportFailureInUnknownLocation(TestPartResult::Type result_type,
                                    const String& message);
class PrettyUnitTestResultPrinter;
class XmlUnitTestResultPrinter;

// Converts a streamable value to a String.  A NULL pointer is
// converted to "(null)".  When the input value is a ::string,
// ::std::string, ::wstring, or ::std::wstring object, each NUL
// character in it is replaced with "\\0".
// Declared in gtest-internal.h but defined here, so that it has access
// to the definition of the Message class, required by the ARM
// compiler.
template <typename T>
String StreamableToString(const T& streamable) {
  return (Message() << streamable).GetString();
}

}  // namespace internal

// A class for indicating whether an assertion was successful.  When
// the assertion wasn't successful, the AssertionResult object
// remembers a non-empty message that describes how it failed.
//
// To create an instance of this class, use one of the factory functions
// (AssertionSuccess() and AssertionFailure()).
//
// This class is useful for two purposes:
//   1. Defining predicate functions to be used with Boolean test assertions
//      EXPECT_TRUE/EXPECT_FALSE and their ASSERT_ counterparts
//   2. Defining predicate-format functions to be
//      used with predicate assertions (ASSERT_PRED_FORMAT*, etc).
//
// For example, if you define IsEven predicate:
//
//   testing::AssertionResult IsEven(int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess();
//     else
//       return testing::AssertionFailure() << n << " is odd";
//   }
//
// Then the failed expectation EXPECT_TRUE(IsEven(Fib(5)))
// will print the message
//
//   Value of: IsEven(Fib(5))
//     Actual: false (5 is odd)
//   Expected: true
//
// instead of a more opaque
//
//   Value of: IsEven(Fib(5))
//     Actual: false
//   Expected: true
//
// in case IsEven is a simple Boolean predicate.
//
// If you expect your predicate to be reused and want to support informative
// messages in EXPECT_FALSE and ASSERT_FALSE (negative assertions show up
// about half as often as positive ones in our tests), supply messages for
// both success and failure cases:
//
//   testing::AssertionResult IsEven(int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess() << n << " is even";
//     else
//       return testing::AssertionFailure() << n << " is odd";
//   }
//
// Then a statement EXPECT_FALSE(IsEven(Fib(6))) will print
//
//   Value of: IsEven(Fib(6))
//     Actual: true (8 is even)
//   Expected: false
//
// NB: Predicates that support negative Boolean assertions have reduced
// performance in positive ones so be careful not to use them in tests
// that have lots (tens of thousands) of positive Boolean assertions.
//
// To use this class with EXPECT_PRED_FORMAT assertions such as:
//
//   // Verifies that Foo() returns an even number.
//   EXPECT_PRED_FORMAT1(IsEven, Foo());
//
// you need to define:
//
//   testing::AssertionResult IsEven(const char* expr, int n) {
//     if ((n % 2) == 0)
//       return testing::AssertionSuccess();
//     else
//       return testing::AssertionFailure()
//         << "Expected: " << expr << " is even\n  Actual: it's " << n;
//   }
//
// If Foo() returns 5, you will see the following message:
//
//   Expected: Foo() is even
//     Actual: it's 5
//
class GTEST_API_ AssertionResult {
 public:
  // Copy constructor.
  // Used in EXPECT_TRUE/FALSE(assertion_result).
  AssertionResult(const AssertionResult& other);
  // Used in the EXPECT_TRUE/FALSE(bool_expression).
  explicit AssertionResult(bool success) : success_(success) {}

  // Returns true iff the assertion succeeded.
  operator bool() const { return success_; }  // NOLINT

  // Returns the assertion's negation. Used with EXPECT/ASSERT_FALSE.
  AssertionResult operator!() const;

  // Returns the text streamed into this AssertionResult. Test assertions
  // use it when S�s)��~��@%����gt5`@}rr�ps����g.�AI��0����B�'�A�p���35�t�jW��j���fWon�Ȏ�����]]��c���%���2������wMIh����ܷ��UŤ�OS,�룚���B���˻�f�m���k$���H�$��:^8�� ��䏠�i��h��f�{FMc�_0���y���2.��I���� �QaPfD���TH�jmr� T�=���:�#t=���)��y
jT��
r�Y�*~ �b�#�	pM]s���j듆0y%���F<��Z#�W����_����EC�����[F>nE̋z��K�cJ�*h�Vs�5�'��,D����o�"��ٖO?�l%��x�sv��
+��X���T71�x"�X�l�;�nf3χ &�,V�
���y���*��\����0Y�a���|nX����&!1���0�M�S�f�����owZ����W��C c�PSv�휹�㴞Jި�qE�c����x����af��W�G&z#���\�'xpu���>�MPd'��t�y�G8V�����N�����\��wV�+~��v�zH�D0u��C �y���� ��\���Oc���\�1���$�f^
�,M����Y�*��JS��SX0���p��fr}`]V�"���P/;�W�f�P@6^���Yd?�u[��p��H��ͳ�	zj�D(��P��q�X�)(
M=��N�_x��OE�Y_�*4�W$�[�3�
�䚐39� �"ӭ��-�zR�z���g=O�4�[���f��;�%7�1���p*�%�I�O�49	�ɗ�j��l�{���՛%���D�e`��]���̸}���K��ף)=z�d����'�
���x*y�M΂m?�V3n���#(�-�)a|� L�g�h7f�M��!If� �6��^@�d��GAD�DtL����ڜ�M�Ͳ#bN��1ϖ�C�Q'&����`|j�Y6����#�"k�6˵b�bJ,"3r9�q:c l��"���zb�Z���;�%�08��mI���8�.?�-��r�z9�w�N+� ��Y���a�R��	b�q�+�]�7yt��_��yLW�	9�PJ�4�����yT��
ӷ­r�I��W�,�>�U�b�Ց?����Qb���B8�`=p]�A��J^����'� XAѕ]u�E�=D]�A�K¢'�}	�ݢT��>fR�X�U���*���։�dq�C@w1��D�vS�i�7�#��CB��a*Ip`��&�\����]h��<��+32`�)c�1�S�͗�H���)�ia��{�l�����=dN��2,}�!5_R����y�^�%3#�K�{���"/�����E��Ə_�����t���0��޹�������j�J�ne�����#�xN��w9�y�x:h�y�_���7?ϑ�x"�=�Q���Y�a�Y�BϺ�7�ꇍg�6�䢫�j�������(
G�� ��"���$�5K�ݚ��w����U/	���>j㛿��9�x�ְr��
mx���kc���<���
Nf��af} �*�
?��z�P1{<t���.�`BT��}:�}��Z �=��`b�@��p��^z��r��~>��}pmQ'�����b�c���q��0��]��6�O*�~��lz�������#Y����
��"��
��^��.��9��/���&o�A7��}��!Џ������4��5-�xʡ��C����Eʡ<P��n�@��_�G�s���}�H�5�n�e/�ċ���
�ѳ����_��O����	��:M���u�}����� �۽Rqk�FO0����C��i�Hu�����77�<��
���6w�v��+Cl�1���zk�:�5�7�Jp[zKl����ؘ�>i|�d�"uމ�6�ܻ�Y�?=����3O<�]9��p��zW�e�����f�����'�s����u�����Ð��n��'�>4۰:⠝�2�r�tX�*���,�E߫5q�oP#�y��|���~E�6�Y� (b���	�Ȫ���h�1˞��N�Nh0�읏8���yRrSp�pd���x]TS=�`GrB�G�\�z���P*��[�7�'`�^^�*��w���Z��q���{G�ϓ����P�B�:����3�2��Э��1<�`�v�\�2w4D5gI�������
6�F��cJ�����/��lh��k�9��i��2�yfPC��f�!�����<��r�/r������C�r�_եM탭J���ɢ�oNn��3Ǘ���yc`�{&Z:1�=o��t<�9+b�FP>�rW�|Egm������<B��5}����
�@aw�p�o��n�{_k�r�:�yJ^�L�}�&��?U�񰔘=��=���{Cg?��ڳ�E̞�wD&�b�v$��e��� �'�l� ��S��zE4����+Zgݒ�m��B��>0��'a�nroɝmBwF��XҺ����=_���#)����X�>��4�xl�� �i7�FA�gՁ�zO�@��1�N4�|��l+D����|  �ެ�9� �M����x����FuOE���%s�ߦ��2�;�;�
t��_��x�����å���q'����5�<��r	���Ff#6Vg(��\�ڷ2��%���DJ����M�l��=��`#ղ`��[�*�5WW�4Ґ�5�4��Rln<��x5e��X$].*������j6��y*�8vܟ�uܿ��±����H'�N�D�H��#C�}Zx@�4�{@��%ZJ�޽�{��5�+���%|~蓰\U3^'�btVS�{U
;kȂ�lA�*[������0c�-#ҷ�kN��.b�����޻f+MU�J�Z�W�����I��Q��Fb�.a��4^õ���czeP�dXM��93
��%uI����xy�.1V]9��[E��%�W��g��[�N*�S<.q��O�<,� �U� �����,mY��	1�1?��nv �7-țI���i������������|�Z�?�_�韟\E�m<[��B2{�&���o���y��������P��&$�]�\wP.�	�^e�+y56�y~��ݘ��ߩ�7x���<K��9-�w0�5yV-}�[����3�;��N�ؚ������>�`�d-`��Xn�=�ԐyZ0]XfU1.�.�m����-E:l,��7�	
�)?�ET�i	�T�b�SP���y���ųtO;J$?ӂ���X7�I�ݤ�lB�Z6G�����-�P�"�y���t�X�>T����la�T�O�zE�C���Q�#���(a
��*xH͹hL�I15�Q��yQ��;��"���\4g��GJ�kӟ���*`�����%MxE{Rɱ��"��0����P���a���F�P�ΨE(ar0a��$���xϥQ·�I��;C�[�oJ�[k����V�������X�<_�Z(�z��<o"���#o�t�ȁ�>l�������)y�/�IPbD ��c�)��ݴSK�~�Fqz��U��c�Rؙ� O]z�%��z����G1o|[u�g�~b�Ϥ��JP�|rs8-��_e	�_[�.-�K0�E|���)�l��B�>���^L�!���׫���nB�x"�kdk��+�`����q̻��Ç8�e>�1�!�\�Cܑ��Vx��:ě�C���'Xԕ�U��Ռ�0��b�ZAycP������,�OR�7G�;��#��i�D.�|m2_⳻�?-@irp7�h+��%��^�q���S� RU_�
R�h�C�}�(lj�F�M�H���y��O�蔬팏[�Ә1]7�����-���MC��&r�~"M�wG�����B�t.�����'�{̥!]Q+u:+Ruө���h�)�N�n:ϔ^eM7�M�S�(��$w�9��OsX<M�C���Sts��s��,8�O�_e�us�}����L��l�J᳹�?!X�T�R-m�Φ�~6�l�^�����b$�r�s�/�Q� �P�&��`)Q�gG�����G�y�����
��_��J㏈/B޿�a�D��I�T�?���&,��6:ugL�r	f������� �6�X^���֖z�3�I8���5+T
7�3��+4�y�hx��7+#���%0l!��],�g�ޜqF��[��b���	D����v�Lui'"5P�w-�8n2+�0���1OJ�{Qp's?�1�~�!���,WF�"郵�K���[:4�M��hX�x
��x�����@����G4�(B���ʉ��"r&0+���OpC��(�����|
7*F���0�O����ϡ�g1��#�]]�z���z�9\�N	�o<��m�4��EQ�c��)sj��x�z�Fscz���!B�u(�@]�'Q:��7�Г~^����5�}8@���~ �`Q�z᥮ٚ����d-Hi��i�|�9VQ�Nvj�E��6Tk��^����&i�߼k�$�R����L|0 c@�EQ�K��B����D8'��$r͞�F\�kl���=����oEə�*�|��>~̐���٪���^�ϖ�e�{�����d��J���L�	�����7O���F!�o���eզ̋�دEG������*ҝ��3��N��`���8��I��6H�Љ�4�4�%K�ߟ�#�<��r���F�s���{�N>S��~���0&����w�׫�z㉤3�5`����o�a�C$#:�:��H}	���&�cl�̻�iT�ƛ��DM�xX���:�<�W��[��.��
QyI���ּ�LQ�7�wG�֒q?��2�EZ�X��ƞ<K�7xB�S�L
��Ddv��_��^�
�ʅؒOh/D�c��JT^����>�q����������'o,`g~���H��'��X�k0ި�@ ��H+�һ\"��W_p�Ի�3����ı��R&�wU�Dz	��%��Ex_���\�n�J���Ȫ����U�Rb)u��yp�j���=qM[΁=x���[�1n��=���@?��g�³�����߽
wm���?�䔓�yj�3�`���T���
f�hH#�����:�*>�W����>��ҷ �_h�{��_!/x��Q�JG�^ \(�����C^���F�ؐ?��3'�<�Ր��_B����6����H쓼6ڰ�۱ tt	82�"��px�V����}��ϰ�qx;wr�٢��(��G��X!x��N������*RH03���<uF�>���>8��w��w�H��0�v��j��&��o(#���+8~��9���0�b*������x�����*����olO���Δ�ɟN��FMО�G�3`+jg��h�yKp�/�Q�W�'�t*��e�b��z��� Mۆن:�aCr�4�w��/o��Δl' �֡�H	Pl�ހӷ��
]�mi弖�-������(v�r�p�2voz�;����������f�~з����4#7�yk�\�]|��{?'*g�PK���F��w����������u���8�[��`L1M��^4!������	�9z�}��mc7b��2�%��<ñ�H|Q0�d?`b��L��(���� d�B䋜����c����{���(��{5u��Sʸ��,�m��ors�2W��W�}D���}.Mh�ʹ��.���Ty�"�y��М%K
Gַ,�䊆�I��:+ˎ����z`���v�>�2;|bm�TD�����|W3��RO���[Yn_��9>?Bϋ#E��Tne!��f���RSp&+,���3Z�.G�K�@��Qo�z�zm� �߀��4 5��o��c�$��D��b��H���e:N�;��v�V���[;�T�Og����{��Q���zߐ�V������\A��h~;�e!���7�/[7��������v7��K�h�`^6,T�4��|Z���/�*����"j́Cj�-^���.9ǉJ��V��7�qV/�e�5�d��¸�w҂�QḞ�ڴ�>J�QP%����(����a�Si��_؁0X��_ư���h�}����r0\~U�.����C���O��?iX�׼\�a��B;ف�$�.�*��L�e��'I �6�׷���=�jP�kb�^��6l�\|y�U���;���>
�"�gn�|�s��X���$o��L�����^��c����T�P�]N�
i��@�
��d�sݕd�uu�+JZ��'�K��Z�OM��&���TE��;��ܬ4�}��r�.`6��b=�ΥRa9V����>YD�J.s3�����{g}�^'y�AD��T�r�b�GH���m������� ���İ5���b�ﬅ�S_��u/�wQ��*�,��H��L��x���O=�����ʆND��)x0MG���e���-ΰ�h�P�����YV�$���);�K�� ��&�����Thz��&��Z��4	^�YVNļK$Ww�|󉽐����4�6qQ(�"4U���%=���B��U#x8���b��q[�ny����	r�$**���e��p��g;Ⱥm���$�⊖�3�z0��x��'ֻ����Q�
�W�_,�<�x�?n���G����s[5��09���qX�U���g\��P����q�ɨ��'�'�en��0�Bziy��E�@�& �S�**�� ���#��R�~ "�\��'��Ϗ���d���p�-<0m�� �=�W�Q�Z���vج��M���:<N,$Q�J�qYq��`�
�W`��*/s�ǉ�}�a�!�_s��%TJ�����f��g�.K��[��)s�[��3��Jd��g�zf�
�b^Ԡr+i!U��hz ��� #�w+����0�]~�1.x7��a��7�5X����"���*,�����:�[���KM��a-cp׫Ǯ�Z�yWTR���u��$ > ����ɪH�	��'�V��J��[JEW�ה��o�	[�CQ⧀fc�#縏��>�!����My�\�_���&[�
�Q��	���.qM�{Q��**���k/ ~t���;���> r��Ѕk���S���'�j�Z��=����w���B��ugm�oj���P��:���:��$���$l�(�G����� �����>����ZZ��4':��/���L�g�Wk�0��Q�Zq��5������__ ^BI@�	�HJ:�Ɏq��<T6<�g�g��ȗ�<�����J{Fah5�D���u�(�#?`�4�b�Iea;(�	0�Saބ2�)@���ڿpnߜ�l]XK9��?����lt�ʹ���S��9-Q̣ ��a�8�F-� U�f�&�NF�&���1�&_}��������%	��s6r��w�D�K�Evߠh[Y6�2}�*�g-�M �/Ly�4��B����_}�WC�\6�em�e+,.��>j��
��$(Ra��ӗK1s��6�>��[Ջ���$�FB���g(YS�y�� �o��`TO�w��w���<�P=cxUR������hȢS�\����<�g�I,�Rv"��-"�[��#B�z�#}Q��Ճl������䈸��8��4RE�̯�ɶV��/ p-/}⢞�P4f)O�G -��2��`�$[������}c8�n���F�7He�_
	�?�������8��h�X��)��|.ŕIr%�F�$���3|���U�I��Y���Ѱ��&��+[W��;\|;���.��u���H���73l��?�<>o >?SE]d폎�;a�|���x\��������ڈ��J�r��������O67u�@�1��κ��o���9k���|.��o8��K��g�
&���;Vކ@����㑔#�_|
�l%�L�K�����m�������pw�*'� T��}����K��]6]�N�����Sˠ�VY��@N�<n91��%ǝGRAv��*��+��U-���d$&�
��]#��6�;V.i�ǝ�@����Q�cl�y��>��Ҟ����X�Ãd�z���w9~�'�|�0�(+�fԪ�����C�Sػ􇆼�z�hUdb�ㅆI�:A� 6T��4~�R��V�G.H�wcbԴ�Z'�4i� ��T���RI��;fԒ�h�j���*��e�9��i�I��$96�%�߁h��M~�xd�����>�&I\P���_�+�_����wIwJwIw�E ��`�wN`�E[��@�M�&M%<�����+���b�ĥI�F9$��A����Ї@(���,'�K������8)+U.�PK�/9,ǳƆ<0Z!��T�-Ǫ�j5�%F�ِo0��U�~�,X2�?_V?*u����5�6����%;ea'���3�SA5�.��r�m
v���k/Uݑ���`t�u$Bo�`���tO-P􏛐�\�@$��\O8KV��z��$'c|�`|P40�S&�W,)��
������W'��Ueǎ�R�
�.�(>���]���	�.`�R�u'~��Pնw�v�.�V͸�6�	D#��j�\�mB��f4b�������~��/%�a���z
�ټ��-�M�?E�a:�cӑK�X�k5}̏raY��s���\�B����d��i0
\���A9����o�7%�BRW_H���J�0������(�
0�'�p��hSć��;�_�h�s P�^�8b�D��O�r�sd�v}p��+��tR�C�1�Յ#U}S����p5�"D��6��%��9=ra�T�_��`k���cmM�i�ʳ�8�DU�9^�n�qF�l��0g
�h�����kHj�8��os��F�>�ّ���E�<������:�[�C�$��Ѣ��G�֛��e�B�! �.�a��[�9�X
��"�ye��w�ŧkd�p�;A9���5r��ߍN���f���}
��= �7��:���� U��_8��:G9��Uz���;a���+�?v-�3)4S��m�˔�n1ZI�� �p���#=L�ؼ��1)���^6�������P��2������l��]�?>=?1��c�����
�ql�j!��t�=5�}��X�	ĕ��`'�Ҋ�uv�v@��Z�{"�5|����:a9[�Yֲ���h��o�$�#Zzǚ�:.t�j�'��I�ߓG �u�Ю���lNqaf O�"�m
p��c��*e��S>&����Q�����}���C��#XRW>�>@\<(��0Z�]ݖ���r
�C`��,�-������6P���|��N1�������n�b�j� �4'F�!� ��)L� e�j����QVl�s�<��W�c��'8@�zd��2�CWqq��2Ԛ��� I.IIj��l�՘�|�,I��H���`��l��)�RN ��Q��!�Tc;e� F#����Y�MJq���zXU�ӎ��Ү�2�#�x�R��`�6��߃��|�z����=.�V,�8>���8>��S���gvq~a�A1/���t�Ȋ�NR>pl\�L5�� 
 T��$A�@�]���c�s"��yӤ}��x��k��ca0 9UE�z}|Z#���"{%�d럜��8����p8��N���s��ʹ <����8Pb,m�ߝ0��=�7;�H���P	�@@ ` E�<�e�y:�~�	>N�����_@Pbl	!��2@*��<�,��P\Ine�C9�sZ�M ���Q�i\���@x{��JQV�}a�@p4�2�A�y��#H���	��Q�>HQ�	|d����yF�w���֗u���gQ���؋�PH�S%ˬF�
zd�ف�>x"y��˼U�Bz��vA�ʙB�^�^">��v'�#����
z�g;t����du
�p7�ND�u`]N`�3%U�*�.�2��-��9�ݔFc��k,z�b������<���0&;���|k��'Ѐ���@���Q4�L`����f�}
npځ�&�1i����G�anw��%@�f�9� �S�2c�cԁ�� �*�=�!�9a�!=����ߥ�ρb ����+�.�<�%Rƙ��?&ƣ9E�8�&'�L,`��É �g�l8�q��*���u�"�,K<��������u�.�Bz��r�����2�L7�����������,����_��>�LY�ʍL�M`"�y���S&�������H*H���0�  ��f���/��~I_�g������}�����O��L�1vi�����5�0��ߦ׷�&��=��j����X�0�GH$Z	U�qBG�#ug�e=�o�W&^�\��[ G�A+خB���mC���&��і���;L4�~JC�8�?��W�]ɞ�G�D�'v�`!c&߯P?a���k�.��t��gt 	HJ��Pz]E�H�B:�mҦ2�F�#�}�`?�� :����Io��N��Il�G~�v�/5��KS�'�_���n�z��M?>l2�`3�vj?~���)�Ny�~��f�/�B[�K��x��A��� �3/���+��<���y��������U�� ���%_�v�z���z�� ���\"�=���:��^����,Z�����oNtpcL�f�alXu������1�1�.���_v[�=��ͯ���=�i��+��Y0��K��{��]��F�j��BzMmD��D8�M|���تW����!�/}ٵ����(FZjL����C]}�S�N;_�w�{����s̯�K�/�r��K���v�¿��%\�����՟?��)׋H�W݌i "�P?6�KZ�5��$gM����3Z��·H�ɱb��d*�a��@��|1�2f�����XYX�_��g@��qHm2]�>�`��XS�>rU�����q�ԍ��>�1���m�1�S��ay�X7�4M�0�W��P/$�{��b���cCj�3��S�@̠�Ȗ4������>qE+<d-1��ֆ��cU���y��C�]0�#�YN�r>{4��x6@="�_����Vc}�t�4-���mkrp�����v�ً��y�a�� ���Ą�Ҿ�l��('�P���qم+�Q�nگɓU�^�ܖ���(������
�|�A�è���QU
$�z	�hG�rGB2/$2��h��!���r�?X��lk>�0����y������,#�����(o�R�)�[ѝ ��2�U���+IvY���r�p���N�%����G\2[�)�����g�;V#q���#���JYH�ky8a�s�+䏀�+�kF&m�>5��^d�p���_�#���r��i�|�����x�-��  ���1��7ߜ�_�(cg��C���!�𲓶l�
Ѻ�N���R�q^�u����Aac�i�V:��n08�����ߑ>�-:b\A94�3LNvL��('"�<����_\	�$��!�N��c����v=��]� tu2�%C0�q�/𕃒DϣR&nOQ��cPX�����` ���mK>(�F|.Q|׎�oc�H���a��-.�W$u��U��ڼ�@��r�-<h�Q7�0�5`r��G�/2`c0�j¬�Y6W*]��W��T�+����BCo}NK�xgN�:�	OT��l��f#�T���icW�IH $Q=��֣\��,vȨl��ʜ��l�p�h���1T�)�L���tP1�OH��>�Y�9�$@T��?�T�)|.S�ҋa����~
��A����P�M<$���� pZ�Ic_"���P/��.�ɂ�`���7ռ�0�1~�O�ǁ�Ҋ�1֫T�B��hk��$?������������F������w���n�Y(��~j�@h�J�G��L���(�̓D�^�������p�� ا�0���o+*L�c,��>�4�Cq��Slx�k�~���A�֏�W�>0d1�ްD6���ڔ@^^H#!������nQ��!�T�D��XU
̎�o;I�Eϐ�q�h�J�"��f�2-��id+��#ͅ�j]x=��P���m��� q�p��"��I�O�nG�Dlv�,��T}X����Y��Z�n�Շ���@���U��5X�J��!�M�J|�2��:5@.I`ҾVݮX$U��>%_����bŕc	��w8%a���S����,r�_�2����21��y���,ħ���exu'�i�� o��E�$��E�F�me�$����T�t
�BXV�=��ݫO�V��P�E�+����&$gO �������,#�������׮ 
 y�:@ *mY�ug&T���e/�@�W�(9-x䀾~4?�5�0u.�xf3�.��3�ΊN�Ձ��4 &t#�c�L��gcTՃf�N��
��x2� ��n��T�`��M��zr+�V��m�VNs�Dno`4p�N�֕���mU�a�p;<�-`�@n��;L�gf!��m6|�>�'�Jh'ȭ��(���A�H�-�pQ��4�����]}���܎�1�ŌT����6cZ��/]vJ~����������!N���Q�W�{t�9���/�+S�w�V��f�|g�#\Ѓ�#|g�9����6{�.��N��+�w�u��bt���O�j�${��tG_��6��%*7�
)&�y��7/��%�s�[������!�_J��B���
�rb����i�r�ء�# �1��z̐�x�|/+d� =nӦw�������(���aý�L^��bj�$�����/�:ɞg�o� ~�d4s���t�xst�3�[�A��Iw�}w�D-
�>�֓��_��I�BXҺK۽����6�O�
|�s�3Kd
v\!Ƃy��.v�T���NQB��^t�t@"��<k�1i˒���,�(\>f������'��Pe1����9t�k`�^�����8���T�"��@�,o��o֕����kٜ��}C	�yDPj�j5;��m�k�7�b�{�����M�5]Gb�?�i_�����0�Ӹ�;b�y��Jy[�ƈf�G���r�2J��Y�9��'cUo��
��`kq��`��ݱ�7i�����x��S��nL;���.��ɍ���IR�ǧ�1�>>Ng�T�}Tbz�Dwe7���!ݧ��j��w�9����}
�+\�-�6G7�ǸC����P���ضt!V�,��89�����{��&�/e�.X��%��*�4��z��K�m8gÛbcP�����m;��=��R�������sÀ!��7hn�E7]G����V�[{k����-�	��P�^��M}��zB��7l]5L��5��9�ꗋ����r���1�f�_�K���+��%��P�ڝ���4�� t��l$b��@���2�Ǒ 
���9��͔@�R��%Ш�>����X��ph3��D�b!ob�[����~@i
�y,�Ou�[���G�,۟1�x�y�Y�HI�q��ɉi����0RK*S��j�Y�}�.˚�) ��K�\���u&2����_$��Hh(���DH���Q6�x�<����HYY�g.��RZ�NF��[��a��
�<��U�S�� �@z��U/O���V�Hc�fy9t�Ic$�r�fW���b`#n��W�g��񣀠@�x��6�@�.��J�]���9Hl��d��G%���&phO����|�쮴��e�J�o�J�6od��}�f�Fbc�E���~�m;E�Ϡ���+]����W�<�F�b|	�t���iZ�K�����	��M�Q|����2����:~���G:"_w�-�_���;J$ q��t2��m�7���{7�*��l�6,r�g)��k����E>L/�U�ъ4��Qʕ(�>1��
�Z�S��.����|k�O��OI���x"�Xo�h��&\����i�����m�%����ڋ���%4�*i�E�*J�6GV:wF�6Gx\���8�v��~��|��ȕ���%�8���d;-�9�C�q����;2���fsz�ʭ�v�T��;H�%�:���Ym��$��L�MW2��V}�|pc�4u͹t�gں��D�)�D�w�ώJj��k���;=�i뢽�� Fkp�G�r�uq����Y9�S�{�:̻�^|���j�ذ��H�,�|���Ãq2�IVW?K�F�����0��L��6}c:#&�L��Lz9�Wg2���L���B<�-}^oP;�T
����82�\f�s��G4�O����0]��e���8�";n�Ι�Y�hjצ�Ԧס�|i�t^T0��A�!���d���vm���zt�����;�?\��_��K�H����z�o!,���L��c�V�@1������cхGK�;�변�bZš?�=�]I[�x-|5b��l%57<�lA���/��)4r���d�Ȫ����~p�5�*�0���z�G�K�.s��A�g�a`Hڲ	y6`�o남�����ٸdة�i���Yjg��.�3N0�1�8�	J�"���9��(��Pi�洤��we�ŕ�ù^��zqy�^<�"�C:�z��_���
�/HGM�+qu_'�~��dG������HKL���@|},e\M��Ֆ)�Ǫ�.�����z{���%�Lo��l�놭
~��Z��;=�[�/��/#������.�Պk��N����U�f���h��%�8�J��?�Ɓ���*�� ��� �E� P
�g����l5� 2��2�̦�?���G_Pfb�F�m��6���Y��ھ�8λ$vI�*EH?����~+<�3��!T��E�����eiU��l�-��Q�3�
�2���{�������'��#�J��
ki����u�Z�U��*�(�~)�*W��{����Xl�C!ι�R���������Ӭ~�i�O�1���9���)�+��p���񒳒Q��B�_fx��~-{Gr=@<!���Vs��d�Z��]��ռsm6�^p-���7��Ewsr-ʢ�C�Q�5�Z��7��r~�[й�|_~q��|��mO�<�W���5�ħ��ǚv�e���T�k3X�OX��S��z�����>[�A��W��6s���
O���Y���z�	��:���;�n���Yc=9��ۻ��6h����h��������)*S�5]��+�Az�?�k�2x��ɰc)�pz�ߘ��|�'v<ev������w�ħ��-�__�q_��>�o'�'΃��UEn�W�a�eM�qU8r�}2M���/�y0��
�U�2TS�&�Z�L����MpJ!����6�c ���ެ��u�qRf)b��Rl�����~���"�t{��T�A���v�}(���fg�2c����ᇽ�p�(�M��4�
.����Ϫ�k��N�C�h��4[Ma,����g���g�%��$�Lm@H��Ayd� ���i�䦾D�m�n��g9���T���цv����6����&$�
�)�}@W�_����"����O{�����:2���ξY_�UL�NE}ɑ;�vd*��w�V^��p�/��ʴm�i+{=7��a]{:�2�&��͞�,fސ)9'礢�������2�e�ۜ�P���#~$��<Td1e̆8��"%���ŷ�4ҁ����E�b�Ɵ���A���PGB�Q�X���2���^�8O<��=��ŕ?�L���jD؉�����!�k���SB�1�}�Dzs�,|�Mj3�����j��b(����|<�z��AR`��&D��c�b�7�㲅s%远�ON�7"�
�j��b�f�lx��\_��r�Wx�7�i����~9��V���Z3Yt�Ň��4��.��9�*�� _
���Z,����F�WKQA;��$�I��5���nz�d�Ota����d�]��-�/���k��)��
\��+���J�x-�dLI������0�Zب�9|�Ct���A���V�N����|`t���LE�h駼@���X���eF��a/|_�q�G�濃�M�1�n��!����+%&����ZL��� s����>����O&W� `ӛ�B���k��w>���"LoV�v.��[�;��g�W��*�������W�����\��P�4�Һ�V�u3��Ue={\���&��K���RG���,F	L�SR�I��5��ϐ����1j���du��9f`a��m���mZ�jH7�F*����X-�>$�S�1�%&g�{�"p1�8�r����z�	�0v���c��:u��σ��&�#/��\I�@�A�L!�N���؍�<|麿�E��I�`I/�%ho�ۅWS����w#ƢZ�x�4�z1�JŤE�5�����+XE����i�+���ϓ��j�\Rkj1�Q&�'�DRui����t#�A���w� ���~	�CB�9!�2Ҡ�z.��c���NLn�;(>Š��%K��-����E%k�dRx'Px7�x����Ĵ��?�a��q�Jp�i`�
�x�,�8A��hM7 ��]�פ�&�/��4lΤ�t
������e��)���&#�ȇ�Z��U잊�{�nu�lq�,���7����"yqe�ҾH\r?~^�wNa
/���ϳ�P�`�8��L��X��
��������ΐ�6c�\C��2X~>�uLa��f�1�!���t��
��j6DQN؁~�f���>{)` <L�+t�˟��e�>��j�� �|>�%F��R%�s����{ݰ�*Uo͕ԀK\���� Dy�}^$ŧ8M���S�Ǫ0�p��NA|
�WHL���֏���+�ܥ$�o��/Q�q#�C=e��_�l`���l,���	�Л�>0�V!ȋ_�����P����ng%�эto���!��ǹ�>��3��Շ`�}+yIm4&o�v�3p��n�r�>�R��n��g%��N����_Y߻�[�
a��j��eW�>kn0i���	KZn0��Q��q/&���LDĚ�?6@h�=�O�"���S!��R��]��T�,�u��G'����咉c�k�3 �K����,m��
v�zy���9�\��b4��D�`�hX�0���Dn��e��	ԫ�!Ue�ʓ���R(�i@�D��ܠ��:���4;��
/i�X!��2��{M#O'��㗯��T���6�����)Qe�����?�#�;u<����:��f���Co�����`�.a�3��09�4\��w8��}��K����ߒ�~���$��?���Ƕ����?�1���'����,�ʰ���V}�gMe޹������)�[O����o�q�$]}�~����җc1���_\ce��콲���e�˸��|x�=�mr���Iz_NÉ�m�R)Vm��wL��^P���n�yTG��e�V=��x��2��g�#k�ª��e�M��q�M<����`4?��"��Qwᖁ�����.0�|�O�^G����̴4C��+S�7?ӷz�%��/1W�/K��Wu��f��x�u��:�!Z�͹z���"�e���*3i�Ц~����t]3��L���N��뾹��m^�J�n�0���R���I;4�0謼�jN5�!i-*�����|�(	yF��t����V�a�:m��LRC��g��F����u$n��"h�$k�w���В̙kK_C�7�m�:tJW�s�g�m�T�2s]�<������	����4��p#Ge�c��Y>�eF]vSj��q���X��n�u?Oor��m�gyF�jx;�����=�V�ޛ����5oH�/�rR�[���X�0��hd��O�ƅ�d�H<pZ�ڸD�����YC��F8o&��������T�V3,��}Yo�{l��7���i�y��b�Ƭ�=U�;/��=X[v�N��3��eϝ����֥W8L�ߣ8��7���+i}��d
���9��S��i�=�_!����U~$\��;��J�^Ө�X��ܥ�����7",��_i�0+)�Ϟ0��{���������ʧ��~�W�O���]����g����/�R�w��A��7j��/C��L�X�s8aU��>�{st��=���MnA��q#`�����0i��)�zH�^ϗ΁达U��w�3&=�1i�a]6��s�lL��^�L���b���/���5��<��I�ʵ?�]� �},(
%��T��r��	�)�l��J� ��+U��t���u��Fba�?��m�mr<�$�!�!u���m܋���պ�})��Q��q��K�I��<X���/g�F��l����T��䱀�	/uP�Tt*{�X�?�\�W�������M��J�nq�=wq�)rX�̽A��Td5�H81]���1�@a�9=t���?֚xP����/��I�QiDG��~���BgYv@��V�����nH�_�y8���|����I�+��1љ'F�X5�3?>�o[�g%^�������t��⫏�ّd�����A�e���=�;>�g�W������S\�$+�e��-!u�<���k��u[J/�W
����7����yyP�1�C\a&n�'F�7>1漐�(6�	Yx�|\�㐰�/�pI�G:|��I
7F���Z!�t
wDVy�{���1�vI��x��%XX�Q,���eaW�Ud���T:�ƻbs��c�z���s/�10��� �K���XH��&�lc$E�o��aA��������Đ�k�f`�H���΋��c<� V&��Ox��s�Ȳ��%��?��8t��dNL���>�~���\�%FL��D��%�=�~��E��ކ��dL��M�(�����2|��t�wC'�vH��XѰ�ϴ�7��Е6c;}�7[�g�['r�&��א
��-�XY���3����?��[%�&Pp��	���#S0?�ٺ��#��!�W;�Z�1H�#���}�����Y6��礢������g���	OX`���)��<��Q��EvY�y�f�W�5���Y�b=�"�u6����ťv��8ё۱H�U6�p�'r1��������J�
Ҕ���C�zC:�[҈��C8���2�8�>x��X��Tj|��ų���1x|!"o�cx=w��O�nc�*�W s�ss&�b슓�l��3��z�m�FVX��I5���7�o����4��)XD�@������m�����*�jE�P�����%�(*���<��B��P*�=�ak�Jm�;��;�;�$����������]�=�=NL��7O7'���Y �t
�J��}Q�x{,�Rf�h�l�"۫�l�`�_�"�`˅ܡt��~��Y�5���]X��e�����GN��T����<�s�]$�nVF2��w��͑��ā1�eE#�ĘN��'CC0N�γ/��hH'�cC$���A���2�}��=
�bZ ��w�BU�2�<�E�	�.a�O.V{��>'f%j�=��Mpި.kf�)�3�V�B�sҖ��2�GX�A��~(8�HF#�6g �
��3�3yT�Oyq|Sl�P�.����L���ʚB�B�:,
m�ǳ%�,��C�� C����XAf�7P�&�|*�r��%�qt�H��R��c���A%K�f��QOo}+�� ]��
������ �m/��q
nm��1��/�;܁��DG6�XYʤ�蒁O�����RV��S�l��mU^���/l��%?�m{��NĦضNx0c��ѱ�<4CT�R.����)
4ewp��Yym-+�]���ٳ�u6+��T���
�Pz=��J�R��w["3m�M3�ϵ$ �Y��X��J�.����A��1�Z�`A��V���`�<��
����<�5���];���]�
�҃��Vo��в��F�G��n`��N�&��>2�6,*w����c�+��'X��l�[�-�_�A���j1Sf��*P��C�0i��BĢ�ȶշ�y�����,uz�[-+՝g����k��ZPeB��g�
zz��DX
��EK�H��L�#J��?o�6,��M�A=����m��aC/��!K�R9A��P�y��CA�=�t[�H���
��[;��= ����}ݘ�w(��BQ��2v@�/�O1�Be�A7�7�-]�ߡ���b������T��e~�Bbkh]�����7����G�=܁5,�g�"|G�Vq}`�T�	ݻ�#C�wbֹ� Hڻ�`����EXbH��`��m�3k�/q�5��o5^��dG��@�&�
�֍��ֵ�Tt^I�SW�qr�4�j�
.q�n���7�nO��m:��"��x{�1��;ae�䔖�PVΣ�:Xρ��[�g���Q�o`����h���ΟBQ�Ig�Q}4��1���˰�_ŲJ�;��bX��N䅆���נw���Y�E��?G��N��'���g+��1��Ǽc�y�'(����Ӿˑ�	~J[�t`������F��'�aŝv{[�-���`lUK-$t��uo��9����^�618������m��]�h��"k�'x�-�)�n���1[�Ǭ�&�8L���((�Q/U�{._N�Q�l��R��s�T��^�������I!��ηЯ25�`{���=�0�㥰�)K�`�6�%�;dC*��>c�I��eΕw��L�JT4Q���ˍ�I
'�o��H60dZL@����+����Q�\�܏Y�-��I2��-Q� � ��� �{�A��p� �� �#����B3�w9r�_ҲQ��)�VpF�
iB�w�]�T���WF�a�R�	@�Nq���iR�X|��Q������}��~~��nB�l�x���0O�l�M	�nvS�6[�ˢ͖`��}Z���X�~��/x%*rMe�ޗP�L���bI$fֽd3&�V�7���IB�f�`S,��v�K��[�9_��t��l��34�s��� �9,<��o�&�q�?f�Y^��g���J��̄��EA���R�^4b�9�_a�$�w*pE����Y�(g�(�l-�u��
+�(�7�#/��0�6ږh8����U{E��Ņj� T��mUm�?�q&�Tf�U�s-Jc�%?��m�|?R�W�1��������c�`�R�ʇ�G�d�_vw�Ү+uu̦+����E�ϥREw�q��C�'�NN��?���l	(�ZE*�A�0���E%�崄��
w fål��M��":�2�yD��C�-��U�AԻ�8�5GX1Ni���k�uS�U)��<�hF�!��LU��xwT���^�9���z����{f
�%N���S��}I�i���2U�;�av^��}�s%�3R��,ۍ�Z�q��!/\n�F����>��C�4O��:����ƽ�Ƈ��n>�~�_B[�m���V��������:F�ϋ.#�8\+L�����s�k��W��)< !jSn�|�1K4��VQ�%�,(��~����!��v~V�m�ӧ�b���G�P��/��T��@�/��w�6�����g
�m\t_��n�o��;�����3b�o`��k'9L�IbȞ��$�T������$�UĖ���
m�w������_�h�k~��x���� o����[��S�S����
�Eo��%\�to�Ӎʯ�s&��=�p�;Q�Ϫ2TI�?S��ИmA-1c9��#�Ɂ
ӫ��z
���N�]tE9z?�a�Oq�|Q�U�+
�S,������ź�
Wr7�'���y�=�؀�8W�k/����N� -<X��|���.`ᛧow�E-��^�o�i�c��'��^�K�$��n�w�L��8F������	���|m=y0��V�����Ƣ֘Dʺ��x����NdĻ�%��)qY��ar=^�$�����q:�00n6Y,,���RL���)��l��fj��̊J�O�3�"���zV)��$�2����Fe�-�� i&ނ���'��1�z��	J�ƛj��W\V����F��P�̛萔�O0Q����Ce�P8ECFEϼ�"�B#���$�h���r��~�Bh����)��_�X=MM��?^��2n`�t��{����"�3pD�wD�=.#�1=J�
oP~����̓�V>�g ��7�1�z��i��Q��V��[N%�A��My�!������[S\�"�G�j&���D�t.��9ws�7<K�hI)�-|��U�]��3pL.�8�:
6m\Z�<Wl\h��z��=-1g�ץS����E
��Lv��s����u�~�&� [ lѼ����ve஗�`08��m59���2�q�� <W��<ͿVlTa
(FR:�^�0��r�cL2w��6��`���Y���*ӗ���0���AQ��i ���=Iu>�yi� ���<5S�(D���z*_�� [_���Yr��~\,�O���+�T�Q���kĿ�q��|Jv�X��V��Y��8���ˏS��'�+�NtH�<67F��B ��Ԃ�Gy�&Rk�`l����9s
Z
 �X�,D+ŪJ��Me�
U�B�z�ax_M���(����|!�RPV�?��&�0�� uo�|�X�|��)Җr7a��>t�?�Y�٨�4_�j������E�#F�aew�4��	����9�{�S���n0N*�z�7E��q�=p�D��zsʋ��R��-�$��	�-(k�Y�d-^A�������`à�j{�u�p�>�_X!3�1uJC�)U�Y]�������ghx��_/��h��*��(��t��f�ʑ��K�h�s��Ƹ���`�%f��ա��,��F��Ύ���x8�Xk��������Ϥk���� Α|]Z�+.�:�"�ۍMC�im�k����?��Oq�%��o��r�tƻ�`7�_�G*D��v�/�F�g�����h��Q] -u����O���@���xL{�c�Z���1)#�ؙݦ`�ˉɭ��5�jP��B� z�Sqe3ϡ��J�mQ�?��Y�cz�.���])E&�5�Ã�����Ħ��I�9�=d������JΙ�t%'��4K��+rkf���3|�J��N1*fg+,�W�n�R:��P����2MW�
a��w�I�c�\��<�&�y�=���L�c�yi������{�Q��`��c�ǼsF�M!���:�������I��}}xab'�'���=Cu�i=�Y�	~����9�,:�CV~�v�ꤐ��A`�ʟ<p�qu�I�<�F32�~�}O���	
������R�{��CBC�=�c�p�T�&s��Dͭ�I�Cnа�1��
H]� �L��?�
r1���6g�6c�d��v�A�<ŧ�%0�g�z}K�i�
�1�M�q�
�0p���*�w��}Fݒ͖�9V��u�(7��o���-��i��f�� �?��?$�Y�I�:}�����(��?�:����n��/����L5v�%�Bڨ7� ��������i�G��E���^㩗��G����ۏ��b!�9�<p?KOS�8��[�8X,M4��Oյ�(�'�9�*�1~, �+��G���X��hHU�R՚!�s�`Hmۀ�ԭhH��N<���^Kf�㛢���QQ�6 �Rc� ��Ch���Pn;���	$ۣ �:5a���=:��B�9�iJP�=FK=_�0b�!�!&9Ky�	��"̣�9�'����n�:9�ף�b�s=3��i�bE^�`������W�Q"N��1�
B�9B�3�����IC�j
6�y� k*&TS����wJ�HX��a�顋�zu�G�3�eּ� zQ���##�)ݲ'Z�8R�J0K�&"p�X���(��t�ŴJT����f*B�Ľd%
�<>��Z�>o����OF$-�����a�t�Xm��I�3� �p�v���v�ov;�7Œez#�!����I��:�h�Կ{�(�f_w:@�ǘ�b�kb�=���H�c�&��gE4��,���~u�7&֒T3c3<�r������8_��?y����O�I�`��I:*�x�V�35QZ����������X��-��B4��y��ʿ=�X�{�C;���2tmM�.a{�ls��h���V�Q?{&�Y���z�r��Mm���-2���0�RDE$YZ��DLt�b���$��B�E\)��݆܅Ą2w1�$W�9���d<���
  };

  AssertHelperData* const data_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(AssertHelper);
};

}  // namespace internal

#if GTEST_HAS_PARAM_TEST
// The abstract base class that all value-parameterized tests inherit from.
//
// This class adds support for accessing the test parameter value via
// the GetParam() method.
//
// Use it with one of the parameter generator defining functions, like Range(),
// Values(), ValuesIn(), Bool(), and Combine().
//
// class FooTest : public ::testing::TestWithParam<int> {
//  protected:
//   FooTest() {
//     // Can use GetParam() here.
//   }
//   virtual ~FooTest() {
//     // Can use GetParam() here.
//   }
//   virtual void SetUp() {
//     // Can use GetParam() here.
//   }
//   virtual void TearDown {
//     // Can use GetParam() here.
//   }
// };
// TEST_P(FooTest, DoesBar) {
//   // Can use GetParam() method here.
//   Foo foo;
//   ASSERT_TRUE(foo.DoesBar(GetParam()));
// }
// INSTANTIATE_TEST_CASE_P(OneToTenRange, FooTest, ::testing::Range(1, 10));

template <typename T>
class TestWithParam : public Test {
 public:
  typedef T ParamType;

  // The current parameter value. Is also available in the test fixture's
  // constructor.
  const ParamType& GetParam() const { return *parameter_; }

 private:
  // Sets parameter value. The caller is responsible for making sure the value
  // remains alive and unchanged throughout the current test.
  static void SetParam(const ParamType* parameter) {
    parameter_ = parameter;
  }

  // Static value used for accessing parameter during a test lifetime.
  static const ParamType* parameter_;

  // TestClass must be a subclass of TestWithParam<T>.
  template <class TestClass> friend class internal::ParameterizedTestFactory;
};

template <typename T>
const T* TestWithParam<T>::parameter_ = NULL;

#endif  // GTEST_HAS_PARAM_TEST

// Macros for indicating success/failure in test code.

// ADD_FAILURE unconditionally adds a failure to the current test.
// SUCCEED generates a success - it doesn't automatically make the
// current test successful, as a test is only successful when it has
// no failure.
//
// EXPECT_* verifies that a certain condition is satisfied.  If not,
// it behaves like ADD_FAILURE.  In particular:
//
//   EXPECT_TRUE  verifies that a Boolean condition is true.
//   EXPECT_FALSE verifies that a Boolean condition is false.
//
// FAIL and ASSERT_* are similar to ADD_FAILURE and EXPECT_*, except
// that they will also abort the current function on failure.  People
// usually want the fail-fast behavior of FAIL and ASSERT_*, but those
// writing data-driven tests often find themselves using ADD_FAILURE
// and EXPECT_* more.
//
// Examples:
//
//   EXPECT_TRUE(server.StatusIsOK());
//   ASSERT_FALSE(server.HasPendingRequest(port))
//       << "There are still pending requests " << "on port " << port;

// Generates a nonfatal failure with a generic message.
#define ADD_FAILURE() GTEST_NONFATAL_FAILURE_("Failed")

// Generates a fatal failure with a generic message.
#define GTEST_FAIL() GTEST_FATAL_FAILURE_("Failed")

// Define this macro to 1 to omit the definition of FAIL(), which is a
// generic name and clashes with some other libraries.
#if !GTEST_DONT_DEFINE_FAIL
#define FAIL() GTEST_FAIL()
#endif

// Generates a success with a generic message.
#define GTEST_SUCCEED() GTEST_SUCCESS_("Succeeded")

// Define this macro to 1 to omit the definition of SUCCEED(), which
// is a generic name and clashes with some other libraries.
#if !GTEST_DONT_DEFINE_SUCCEED
#define SUCCEED() GTEST_SUCCEED()
#endif

// Macros for testing exceptions.
//
//    * {ASSERT|EXPECT}_THROW(statement, expected_exception):
//         Tests that the statement throws the expected exception.
//    * {ASSERT|EXPECT}_NO_THROW(statement):
//         Tests that the statement doesn't throw any exception.
//    * {ASSERT|EXPECT}_ANY_THROW(statement):
//         Tests that the statement throws an exception.

#define EXPECT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_NONFATAL_FAILURE_)
#define EXPECT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define EXPECT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_NONFATAL_FAILURE_)
#define ASSERT_THROW(statement, expected_exception) \
  GTEST_TEST_THROW_(statement, expected_exception, GTEST_FATAL_FAILURE_)
#define ASSERT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_FATAL_FAILURE_)
#define ASSERT_ANY_THROW(statement) \
  GTEST_TEST_ANY_THROW_(statement, GTEST_FATAL_FAILURE_)

// Boolean assertions. Condition can be either a Boolean expression or an
// AssertionResult. For more information on how to use AssertionResult with
// these macros see comments on that class.
#define EXPECT_TRUE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, \
                      GTEST_NONFATAL_FAILURE_)
#define EXPECT_FALSE(condition) \
  GTEST_TEST_BOOLEAN_(!(condition), #condition, true, false, \
                      GTEST_NONFATAL_FAILURE_)
#define ASSERT_TRUE(condition) \
  GTEST_TEST_BOOLEAN_(condition, #condition, false, true, \
                      GTEST_FATAL_FAILURE_)
#define ASSERT_FALSE(condition) \
  GTEST_TEST_BOOLEAN_(!(condition), #condition, true, false, \
                      GTEST_FATAL_FAILURE_)

// Includes the auto-generated header that implements a family of
// generic predicate assertion macros.
// Copyright 2006, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file is AUTOMATICALLY GENERATED on 10/02/2008 by command
// 'gen_gtest_pred_impl.py 5'.  DO NOT EDIT BY HAND!
//
// Implements a family of generic predicate assertion macros.

#ifndef GTEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_
#define GTEST_INCLUDE_GTEST_GTEST_PRED_IMPL_H_

// Makes sure this header is not included before gtest.h.
#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#error Do not include gtest_pred_impl.h directly.  Include gtest.h instead.
#endif  // GTEST_INCLUDE_GTEST_GTEST_H_

// This header implements a family of generic predicate assertion
// macros:
//
//   ASSERT_PRED_FORMAT1(pred_format, v1)
//   ASSERT_PRED_FORMAT2(pred_format, v1, v2)
//   ...
//
// where pred_format is a function or functor that takes n (in the
// case of ASSERT_PRED_FORMATn) values and their source expression
// text, and returns a testing::AssertionResult.  See the definition
// of ASSERT_EQ in gtest.h for an example.
//
// If you don't care about formatting, you can use the more
// restrictive version:
//
//   ASSERT_PRED1(pred, v1)
//   ASSERT_PRED2(pred, v1, v2)
//   ...
//
// where pred is an n-ary function or functor that returns bool,
// and the values v1, v2, ..., must support the << operator for
// streaming to std::ostream.
//
// We also define the EXPECT_* variations.
//
// For now we only support predicates whose arity is at most 5.
// Please email googletestframework@googlegroups.com if you need
// support for higher arities.

// GTEST_ASSERT_ is the basic statement to which all of the assertions
// in this file reduce.  Don't use this in your code.

#define GTEST_ASSERT_(expression, on_failure) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar = (expression)) \
    ; \
  else \
    on_failure(gtest_ar.failure_message())


// Helper function for implementing {EXPECT|ASSERT}_PRED1.  Don't use
// this in your code.
template <typename Pred,
          typename T1>
AssertionResult AssertPred1Helper(const char* pred_text,
                                  const char* e1,
                                  Pred pred,
                                  const T1& v1) {
  if (pred(v1)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT1.
// Don't use this in your code.
#define GTEST_PRED_FORMAT1_(pred_format, v1, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, v1),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED1.  Don't use
// this in your code.
#define GTEST_PRED1_(pred, v1, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred1Helper(#pred, \
                                             #v1, \
                                             pred, \
                                             v1), on_failure)

// Unary predicate assertion macros.
#define EXPECT_PRED_FORMAT1(pred_format, v1) \
  GTEST_PRED_FORMAT1_(pred_format, v1, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED1(pred, v1) \
  GTEST_PRED1_(pred, v1, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT1(pred_format, v1) \
  GTEST_PRED_FORMAT1_(pred_format, v1, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED1(pred, v1) \
  GTEST_PRED1_(pred, v1, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED2.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2>
AssertionResult AssertPred2Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2) {
  if (pred(v1, v2)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT2.
// Don't use this in your code.
#define GTEST_PRED_FORMAT2_(pred_format, v1, v2, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, v1, v2),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED2.  Don't use
// this in your code.
#define GTEST_PRED2_(pred, v1, v2, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred2Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             pred, \
                                             v1, \
                                             v2), on_failure)

// Binary predicate assertion macros.
#define EXPECT_PRED_FORMAT2(pred_format, v1, v2) \
  GTEST_PRED_FORMAT2_(pred_format, v1, v2, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED2(pred, v1, v2) \
  GTEST_PRED2_(pred, v1, v2, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT2(pred_format, v1, v2) \
  GTEST_PRED_FORMAT2_(pred_format, v1, v2, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED2(pred, v1, v2) \
  GTEST_PRED2_(pred, v1, v2, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED3.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2,
          typename T3>
AssertionResult AssertPred3Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  const char* e3,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2,
                                  const T3& v3) {
  if (pred(v1, v2, v3)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ", "
      << e3 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2
      << "\n" << e3 << " evaluates to " << v3;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT3.
// Don't use this in your code.
#define GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, #v3, v1, v2, v3),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED3.  Don't use
// this in your code.
#define GTEST_PRED3_(pred, v1, v2, v3, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred3Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             #v3, \
                                             pred, \
                                             v1, \
                                             v2, \
                                             v3), on_failure)

// Ternary predicate assertion macros.
#define EXPECT_PRED_FORMAT3(pred_format, v1, v2, v3) \
  GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, GTEST_NONFATAL_FAILURE_)
#define EXPECT_PRED3(pred, v1, v2, v3) \
  GTEST_PRED3_(pred, v1, v2, v3, GTEST_NONFATAL_FAILURE_)
#define ASSERT_PRED_FORMAT3(pred_format, v1, v2, v3) \
  GTEST_PRED_FORMAT3_(pred_format, v1, v2, v3, GTEST_FATAL_FAILURE_)
#define ASSERT_PRED3(pred, v1, v2, v3) \
  GTEST_PRED3_(pred, v1, v2, v3, GTEST_FATAL_FAILURE_)



// Helper function for implementing {EXPECT|ASSERT}_PRED4.  Don't use
// this in your code.
template <typename Pred,
          typename T1,
          typename T2,
          typename T3,
          typename T4>
AssertionResult AssertPred4Helper(const char* pred_text,
                                  const char* e1,
                                  const char* e2,
                                  const char* e3,
                                  const char* e4,
                                  Pred pred,
                                  const T1& v1,
                                  const T2& v2,
                                  const T3& v3,
                                  const T4& v4) {
  if (pred(v1, v2, v3, v4)) return AssertionSuccess();

  Message msg;
  msg << pred_text << "("
      << e1 << ", "
      << e2 << ", "
      << e3 << ", "
      << e4 << ") evaluates to false, where"
      << "\n" << e1 << " evaluates to " << v1
      << "\n" << e2 << " evaluates to " << v2
      << "\n" << e3 << " evaluates to " << v3
      << "\n" << e4 << " evaluates to " << v4;
  return AssertionFailure(msg);
}

// Internal macro for implementing {EXPECT|ASSERT}_PRED_FORMAT4.
// Don't use this in your code.
#define GTEST_PRED_FORMAT4_(pred_format, v1, v2, v3, v4, on_failure)\
  GTEST_ASSERT_(pred_format(#v1, #v2, #v3, #v4, v1, v2, v3, v4),\
                on_failure)

// Internal macro for implementing {EXPECT|ASSERT}_PRED4.  Don't use
// this in your code.
#define GTEST_PRED4_(pred, v1, v2, v3, v4, on_failure)\
  GTEST_ASSERT_(::testing::AssertPred4Helper(#pred, \
                                             #v1, \
                                             #v2, \
                                             #v3, \
                                             #v4, \
                                             pred, \
       ����$�z:Z��a����2Y�n.K�Gn��z_8��z�H�"
���[4�h���{��%�cQcy�����%8�T3v�"�®F�"�kQp;����Q���L���y2��f˱�D�a꯿����XW���_,Z�b��[XO�S��GZ�ُn�߮��Y�7�d�s�G�����aNs�7��:¼EI$tz�CN�N0�+�@��Cє���+�8�[��C~E	�������8j��C`�JM-i95�!v�����OR��\���$w�'D�x� 0a�=V$w�7H�'�\vܝ¢�xz]A�w�F/Ǒ]!�ǣQ=@fM �pT%W�`�Y�����J	:-IG�/6ڛ��V�\?��֦\3kӭ�:?)�|�@wfs�mi�l<'�����&ݽU~-϶Dm�#��8��&�D��Pr������(���7e6��~���fLRmG�� ����������>-w)$
��xu>;i��H�{7ԇ壃Y�[ڏ"PG�[ܚ�#e7�!q�#����7��� ��)�׍�ru�uӁn�����9"�w��iǦ���`��M�J���9�mpw����aM��Ӓ�}[���ǐp�f4#�¬�ݖ=لx	�`���,n�nՀ��e��I�E�����}d�`���G,˰���D�����@%+�����BW:հis�lGPe��Q$c��P_po��eo%���NE�Q|�@А�4��1Di3�K��^Ȥ�t3���?G��X'��[N7SP�������$���d��"��@�.-i�Kg��1�ɐ`����hU��ހ7�m��ߥo���?��,�X�Z<p�u��x��Ħ��29n�~`����Y����0[�T�!L�5zxПCF͹�����#���$��#,�(t=
	 �R:X��lqKe�X�(��ˇ�y��k��U��W̤�[֣���Zh\+��$���
�gG�B�n��?vEz�(�[�H��9�/;M��ӄ|����cM�2�f?*��ò�v�"��`ݥ����g���jz3s5���k����#o�Q<T�
	�m^�b�����IPw���J$���4aL���|B����1iZX�+M�#�˪�VY���u�h
��xK���;rN�s��υ@�=4®U0���&~��,]����W$`_�~��Ѵ��g�.��An�2a"f�y� 6�2{��a�#Z Z=^�>�B��B�ycnLbjTDK���r�&B�-96
�p4�V�S8��I`l��ˍf@��,��7�lECIz	2���tѽ�W�K7�_z2��2���H�w߷�p'JI)4U���8b���8f�J6��*�(i�4�[z	R+�6�@G�O5d�O���Q��X񣱆)#L
a���h���m"���"���D�M�lt4N���"��,�C͍
5���g*�����q�%K��:��E�~������y.Ce(�E�Ρkf)q]��m����?��7k�Å��L�����0%P<�$+�W�_*/�>sj/&�m���{9|_�C��k|ȯ�csA*���H-������]��>��+�F�����|8zӷ�b!�Ù1K�(U/��ϝ �[�?�|~)���/P���]�9SW�&���+�#��yVo6Hp�&�2�"�Q.�K����Ѷhp�APONJ�f�~5�ƫ@ٻp�3��Є%�iMDK�q����tS7�ICb\������QV�['�W y2�8��;ϐ5�,i'�sg�.x%)Ep#��x�_Bp�N�������"`"p�e(��
�Z���:���[!+O��Cs'?#�uPL�
�����,\b�B�%��-�,�Я:�e�?��#���|��\f�w��>X�܊xu��~�ޥ��u!#���E�1���H��x�n�D�@�t˥\|�]8��8�l&_{����`4�	�z��~.���c{�f��.hU�ix��Wؖ��Is��v�W�ES�7���=I=웭���kT�M7b߲r���������������62�_���U��T�זD~���+�iMT>VX��q�����\CW;U��|t�!���$E��>�w��'3�4�8P����z�N���z���f�$l�U��7'���8l<�7�F,Oa�x�sR`�F�*�!KD�>i�`~�h�DNݿtI�E��2 ��8�<RH.����PrOi����\���|������t�Ƌ��6@"�Px�f���p�Ve)���m;��6�2�w�WE��1���q�"�CptuF����9�nG��c�49U�͋�2�-�@X
$�zu?Q��#Y��%V������(���z�.��G;�Ekig��T
��#��o��^�M8Ҹ'L�v�(��n8MU�@,;����X���|���xօ�F*�W��ȩ'��Dj���*�'2��<w��L*�WuTWD��۬��ل�(�������8:�b����K��ĭC��jP�M�K�5oL�Xw"9��W��cI2G�=I6��~�#���"�����d^y�~�|sK͆�:Kͨ�FKM��/?�R�i��h��sb(r�"o3�v+���v��Kx5ي��3J	�~�9�Lc�
�Cͼ�
���o��5�%�#��[ñ��$=���G�E��;�S��O�����}�n=^��gKG�4A���Kҗ�Y��I$�����]�BK6����tY����,Vs�]{l>�d������.�Ȥ ��l�ࠂ��Gm�E�W�֣=(?�t�6�$����^"�ZY~�tfx�w����n��2���w���<�����ؐ��g�DOЏ��వ��I��odޅ��rR�������{��j����w�x�Ih���Eh�m|�![*�#v�Z����>�ѕ����F�Ԍf.��b�:e�V��se��S����*л�MS�v�?��("�u6z"h�v��_f� ��f�J0j�VN ����$�g0P�J����/n�*,T ���䠩�k}9w�s��8���
�>�M�v��j?n�"���|���WF��72��
�%K�,T��d�ӛp��mML�N%x�<���1�^Dl^ꦀ���w[�3�Ԏ��δ����������h�1�KjgP����J�PF.�T�4yƴ���C[f*!�{�&�d�e�����_��,�b��!���d�*9<N�$�f��8�N�O�*� M2����X~6�s7�#�n���1�L�t�_�"��-�05؂��������m�U��>Q�J����tD���Q���@��kWMMj��ܥq�f�۝���q/�ӣq���I����78�פ����iG� o��!V[�5
"}����Ɨ�'6���\o^/�72/3�(�Q
�Ɉ�寝!5�2��>��ߠ��������2���M�,�;�83��G���K��O9}�
u�}:��'<���JB�y%�G�"@�+4��V$*Ch�yk�g��I��㗆�\}�-W���%�%O�A2>߆������:J��W8�����KM��1��^MJ����D-V_ɮİޣ
���~q42; Q��Ѓ�DN������ZQKr.U3�l�B��|�>G)녘��E�|z��uq�!V�ѳ��t���a��V,��)%A��B
����Z<m�ƕ��\�5N,�z�]�W���n<�	��V��ֆ�̣8��S�U�bR�gS�,�����	��:13@��X.�QX�ԥ�^	KT�޶��Գİ�X?P߀U-5��:��:p�T�E�޸��:v
��I���R yT�u^௘޹d��d����(B?N��57	��Ů�6�6��I�n���7�j�:��.�_j�h7@���{�1KMYEZ�!~J�P�*��:7뷎��h��,����%�O��`��~�X��ô����_�9N���d�<9'�GǪ�i�+���U������z�n�{����U��{��a�9��3�9�P\��e��̡���}��$5��+�e�Q^ފ��d�皳� b��f8���=���Hې�BL�5�X��m�ǧ����n�1�r����P\��f��*�`�_��1��sW/6�#��o;�'�+��R,�
�Yn�,3'�j[u9�AF�\�̽��W�,,姓�޷����&��t�	F���髾�/t�o߅��{I�G�SF�3?�|����Hd\�L�c�u�V��No�6�\)�HT��Nl��\X�~��]
�6)7� ��Ըo�Ұ:�k���X?w(-��""5c�	�F���(QK�Ɨ�ƛ8�)�����5�gF��i�Os�0ָ��
*O�\&n1:;.c|����h�|u#�_��>�(ֆ���+Ө<1��BZ�i���-,(Y#-�_4��\��-���M���^9�u;,��K�*o����/Ă��Y|�:��	s�R%ciay����?flp�$F��#~"��Q��Yt�X���$����5xĂ.� dU1z
��{� s
�yrsK��D�EwByd�J��K�e�Qv�Ÿ6��6�FE֬ ,�
�zl�6O��Z�|���oa
,��η��u��eB�����5���])�j�r�Jz��U6?��3oɥY�o����w��U��X��Hŭ�ݴt0ֿz�v�
�$_����S�QZw�푌�OO�$�/�<�9�޸ΐ��/-�1���H+�{�a� 5m��>�gKb���H���R�"Rؑ".�����B�P`@���!ȏ���)};�J>�ʆ�\Ζ����IŌ
���fC`,�c�}�~�o�]�_��9o�Ŧ���F�w�P˫��_�x�+�"��C`ig�A��zN�c|����l2mr�$R����9�Ydի+����"��X0k����8�-.��O���v�g�w���� ����!߸.�.v�����vֵo�A��Oqѡ1���|�G;h�v��h���k4�%�̀leI���b$��Z�`�'S�g8�*?e~�_�q#�e��'w�Z�4��*�ӕ'�֙��=���e��h�o1
?jO�Gݘ��=\��ȴ�_��u���\)�πW�$#���x*򛖧ѝ@�v�lmn)r�9�vR��3a��JQ|�+�6�)��ʋ�n&��<�"���av��K/f|��� �`{��U��lؘN[7�p6�t#ϫ��f��f��́����� 7�|ci��&���6_��m��^T�bQl��~%nW�[��k[x߲�ǣ��Yc�D+�DuKM�$cI���PD��yH)��MhW.p����a���Z�Z�ǈĪ��@LUQCE�*��n*�mVm��ő���xUUuT�^�!=�Fb���*������Ou+������u����l�Z�_����w��8>�Y�6�U���]Iۘ��ա��VHi��ͽ��,n��%��ߠ��B��L#����ܸ>����]

UU�B�r}�'�
J�"��xZIIn�$9]�)�3aItݒ\HIF~�(��a�^����Ғ�nV�e�=�<�W�����������·=�b�^m��x����µ˅��bQ/j{(O]!�g�qb�e����0��=`���0u-�D���\D�6LO����rl�w��#VL�)��؀�M�yQ)-"�灸2?�K���AV�{p5�7�W#��F���I�ձ��z5�2��te���i��{"9LL"���s
S�ӓ%uK*�������i���h��A��.>M���y��X?��g��>7����uːc!p�M�+��
��V�������.�U!���=�c5�U|5��G�+�obN^G��#Ş�5x�A���j��j�����	j|�,Z���ʧ������>rІ6�Ə�=W�o��]�/V��z ❙0%6�#z?c==�n��v!t�|6?)RMh�	�4��!���!��465]%vR�ˉ��>G,���4�:_�7�u�4�� �����4�'Hg��J�bnfE�YK\7m��&���W#�&��uW�#i˷P������m��W��ZB�dP
�6�t����x��뗺�Sy���E���,<4�uj�+E=�,�[��NG��a���M��m�7�ɟ�[�=z���(�a�Y��9boҥ���\�LE�����d��>��=�DBȇf����T�ᰝ�n�8R�=THSZ�4]��3;[y���@�Ϯ�A^ڙɃ��$���Q�+TJ3��'����K�h�n0g�
�Pۆ�
�#+^����Ok�C߈�%�mV�N4٩V ��yRm����������xR��0Sĩ	2v�F�\���琽�d\�y�/����:�G�Z|(�n��{����Bng�T��C�E��/��e�Z�o}=<T��QN�`�j��T]��B^Q�Jmc���dcPQ�A#�����=�������#�����鶣��"^�T�f�ZM�?$Oj�;���	��Z��F���x(���A寽D�_��ϏH�J$϶j���EE�bl�Z6���L��p1H�Q��Co����`3��m�������=��e�â��e�������e�c�N�z�e�黗P*^�
~4�o
-�&�/�P�D��א��� ��,w��)��{����R+��Wő/?�.B�b:��3l���M�l荀���w�0#id�5sĿ3x��4��bhϟQ��h�x0Y�ؕ����m��X���5��\v�<~��Ēj���u���;h�T��;%ɣ#v�z����
��d{����H;+.�Κ:Y[mS�@�=/�&�P�
Ԑ�]ŴN"�p�*�5[[fe���Ď:kq\&uh�A��V<4IIT�@^4����u�򃃥�bՊ�k!+�akKV�0D�׫�Y�և���I����J	j������;f�;&D���pJ��pù!;Mט??�?�&� 
>P�P�5���c𘛡V9��_i#�&��G�H�y�绖tn#���Ba���"�����D��;�6a(��`(�%����O�qצF���c��T��=�,^~@Q���Etc���"|��/ǫe��a�(�δl��5�t蓎$�C����;��UtT{�}�>p+=ʁ��GG�|C�����������]��
N,�.> ��Es`���:���Y��c��zn��W��g=�Y�32^��>8����F�E<�F��e'/e�ٕү{)�v�5r�M��H=�7{�f�7MI/^��+�e��90� �e6_�^�����Hc=|r/�ȅ�ȅV��A=J��R�i�췧�!�٤����v�%RHK�{�pC����IQ��iFﳈn��Ө�2��X��E�.q��Z������zh��RmT����2:2K�6p��#R=�WȆTR�i��������%z�:��j�=f��7�
N�8���B��RYXOt������ŏx,y�����EW�XӒ����ޑ���iZ�����f6UDf8�`����f��ڭ�on�hզ�T*�b�BoItZ��>�֔ӿ�~�뾶y�%�?@�F|�~;�+������{�Jrg��94��05�Dj0���Z�d꟠�0� {�v����*76�����y>�<(�<����4#w�+��?�I�&0Z
ƝM�޸)i(+��6:# ���
̆�䐎���g(�*S�gf4R�!}��H���^�R�r��)Rz����E�	���[�a���g���v��{�I"&<��?.�c̏���L^И
�Wq[�
��{�%I�����d�a�a�I�A��TJ�n��!�m�s9)�ʷ�dɳ-ٿ�M�
���3Qa���&	 �t���=(W��C!��f�F
Ocv��)��nѹLdx焥!"�"}t"���DO'�F���P�%�p �_���n1Q��2H���Yx�[�$w��͠Rȏ,CAF���べ�G���j��X�5�����N��*o.mj�'��T|3�F�`���`��M�� 7O'�o�x�f���ͦ5��+��W0�fq�cW=q}!����uQ�����%�͞��-�2[�Z�{�"�/�>�������XJ��(��u�q��t�]�x���nXt�/=nI�<"��?~���f]�>�x��Զ@�������%ϗz񕁬�j�aQ�Y��c\���N�i�P�x�e
Zд�