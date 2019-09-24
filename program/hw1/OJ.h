#ifndef __OJ__
#define __OJ__

#ifndef __HIDE__
#include <GL/glut.h>
#endif

#include "Point.h"
#include <iostream>
using namespace std;

struct Verify
{
  public:
    bool verify(int n, vector<Point> &points, vector<int> &match)
    {
        if (!verify_input(n, match))
            return 0;
        if ((int)points.size() != n * 2)
            return 0;

        vector<Line> lines(n);

        for (int i = 0; i < n; i++)
        {
            lines[i] = {points[i], points[n + match[i]] - points[i]};
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (intersection(lines[i], lines[j]))
                {
                    return 0;
                }
            }
        }
        return 1;
    }

  private:
    bool verify_input(int n, vector<int> &match)
    {
        if ((int)match.size() != n)
            return 0;
        vector<bool> vis(n);
        for (int x : match)
        {
            if (x < 0 || x >= n)
                return 0;
            vis[x] = 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
                return 0;
        }
        return 1;
    }
};

class OJ
{
  public:
    vector<Point> getInput()
    {
        return input_points;
    }
    void set_match(int i, int j)
    {
        if (i < 0 || i >= n)
            return;
        if (j < 0 || j >= n)
            return;
        match[i] = j;
    }
    void set_match(const vector<Point> &P)
    {
        int n = (int)P.size() / 2;
        for (int i = 0; i < n; i++)
        {
            set_match(P[i].id, P[n + i].id);
        }
    }
    void display()
    {
#ifndef __HIDE__
        auto &P = input_points;

        displayConvexHull();
        displayPoints(P.begin(), P.begin() + n, 1, 0, 0);
        displayPoints(P.begin() + n, P.begin() + 2 * n, 0, 0, 1);
        displayConnects();
#endif
    }
    void drawConvexHull(vector<Point> P)
    {
        ConvexHull(P, CH);
    }
    OJ()
    {
        auto &points = input_points;
        cin >> n;
        points.resize(2 * n);
        for (int i = 0; i < 2 * n; i++)
        {
            auto &p = points[i];
            cin >> p.x >> p.y;
            p.id = i % n;
            p.color = i / n;
        }
        match = vector<int>(n);
        for (int i = 0; i < n; i++)
            match[i] = i;
    }
    void verify()
    {
        if (!Verify().verify(n, input_points, match))
        {
            cout << "QaQ" << endl;
            return;
        }
        cout << "YES" << endl;
    }

  private:
    int n;
    vector<Point> input_points;
    vector<int> match;
    vector<Point> CH;

#ifndef __HIDE__
    template <typename Iter>
    void displayPoints(Iter begin, Iter end, float r = 0, float g = 0, float b = 0)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 1e9, 0.0, 1e9);

        glColor3f(r, g, b);
        glPointSize(5);
        glBegin(GL_POINTS);
        for (Iter it = begin; it != end; ++it)
        {
            glVertex2i(it->x, it->y);
        }
        glEnd();
    }
    void displayConnects()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 1e9, 0.0, 1e9);

        glColor3f(0.5, 0.5, 0.5);
        glLineWidth(1.5);
        glBegin(GL_LINES);
        for (int i = 0; i < n; i++)
        {
            auto &p = input_points[i];
            auto &q = input_points[n + match[i]];
            glVertex2i(p.x, p.y);
            glVertex2i(q.x, q.y);
        }
        glEnd();
    }
    void displayConvexHull()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 1e9, 0.0, 1e9);

        int n = (int)CH.size();
        glColor3f(0, 0.5, 0);
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++)
        {
            auto &p = CH[i];
            glVertex2i(p.x, p.y);
        }
        glEnd();
    }
#endif

} oj;

void display(void)
{
#ifndef __HIDE__
    oj.display();
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
#endif
}

void naive(vector<Point> &points);
void DC(vector<Point> &points);

void solve()
{
    vector<Point> points = oj.getInput();
    DC(points);
    oj.verify();
}

int main(int argc, char **argv)
{
// set up openGL
#ifndef __HIDE__
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("ham-san cut");
    glClearColor(255, 255, 255, 1);
    glClear(GL_COLOR_BUFFER_BIT);
#endif

    // solveing
    solve();

#ifndef __HIDE__
    // display forever
    glutDisplayFunc(display);
    glutMainLoop();
#endif
}
#endif