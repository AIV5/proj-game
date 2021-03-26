#version 460

float pi = 3.1415926535;
float lambda = 1;
float eps = 0.005;

out vec4 fragColor;

uniform vec2 hr;

uniform vec4 playerP, playerR, playerU, playerF;

uniform vec4 point;

uniform vec4 l1, l2;

float distPoint (vec4 p, vec4 v) {
    float t = abs(dot(p, v));
	if (t > 1)
		return 0;
	return acos(t);
}

float distLine (vec4 v) {
    vec4 acc = l1 * dot(l1, v) + l2 * dot(l2, v);
	float n = length(acc);
	if (n > 1)
		return 0;
	return acos(n);
}

void main () {
    vec2 normCoord = (gl_FragCoord.xy - hr) / length(hr);
    float polarRad = length(normCoord);
    vec2 polarTrig = normCoord / polarRad;
    float alpha = 0, dMin = 2 * pi, dCur = 0;
    vec4 look = playerF * cos(lambda * polarRad) + (polarTrig.x * playerR + polarTrig.y * playerU) * sin(lambda * polarRad);
    if (dot(look, playerF) < 0) {
        fragColor = vec4(0, 0, 0, 1);
        return;
    }
    vec4 t;
    int k = 0;
    while (k < 500) {
        t = cos(alpha) * playerP + sin(alpha) * look;
        dCur = distPoint(point, t);
        if (dCur < eps) {
            fragColor = vec4(1, 0, 1, 1);
            return;
        }
        if (dCur < dMin)
            dMin = dCur;

        dCur = distLine(t);
        if (dCur < eps) {
            fragColor = vec4(0, 1, 0, 1);
            return;
        }
        if (dCur < dMin)
            dMin = dCur;

        alpha += dMin;
        if (alpha > pi) {
            fragColor = vec4(.25, .25, .25, 1);
            return;
        }
        ++k;
    }
    fragColor = vec4(1, 0, 0, 1);
}
