#include<bits/stdc++.h>
#include "Functions.h"

using namespace std;

void canon_primal(int &p_vars,
                int &p_cons,
                string &scope,
                vector<int> &obj,
                vector<int> &RHS,
                vector<string> &signs,
                vector<vector<int>> &consr,
                vector<string> &domain,
                int &pc_vars,
                int &pc_cons,
                vector<int> &pc_obj,
                vector<int> &pc_RHS,
                vector<string> &pc_signs,
                vector<vector<int>> &pc_consr,
                vector<string> &pc_domain)
{
    // vector<string> pc_signs;
    // vector<string> pc_domain;
    pc_vars = p_vars; //number of variables in primal canonical form
    pc_cons = p_cons; //number of constraints in primal canonical form

    pc_obj = obj;
    pc_RHS = RHS;
    pc_consr = consr;

    // vector<vector<int>> og_cons = cons;
    // vector<int> og_obj = obj;
    // vector<int> og_RHS = RHS;
    // int og_vars = p_vars;
    // int og_cons = p_cons;


    // for(int i = 0; i < p_cons; i++){
    //     for(int j = 0; j < p_vars; j++){
    //         canon_cons[i][j] = cons[i][j];
    //     }
    // }

    //breaking the coefficients for unrestriced variables
    int colCtr = 0;
    for(int i = 0; i < p_vars; i++){
            if(domain[i].compare("P") == 0){
                pc_domain.push_back("P"); //positive variables need no modification
                colCtr++;
            }

            else if(domain[i].compare("R") == 0){
             pc_obj.insert(pc_obj.begin() + colCtr + 1, -1 * pc_obj[colCtr]); //breaking the obective coefficients

             for(int j = 0; j < p_cons; j++){
                pc_consr[j].insert(pc_consr[j].begin() + colCtr + 1, -1 * pc_consr[j][colCtr]); //breaking the constraint coefficients
             }

             pc_vars++;

             pc_domain.push_back("P");
             pc_domain.push_back("P");

             colCtr++;
             colCtr++;

             if(colCtr > pc_vars)
                colCtr--;
            }

            else{
                cout<<"Invalid variable domain!"<<endl;
                exit(0);
            }
        }

    //breaking the constraints for equality and unfavorable inequalities

    int rowCtr = 0;
    if(scope.compare("max") == 0){
        for(int i = 0; i < p_cons; i++){

            if(signs[i].compare("<=") == 0){
                pc_signs.push_back("<=");
                rowCtr++;
            }

            else if(signs[i].compare(">=") == 0){

                for(int j = 0; j < pc_vars; j++){
                    pc_consr[rowCtr][j] = -1 * pc_consr[rowCtr][j];
                }

                pc_RHS[rowCtr] = -1 * pc_RHS[rowCtr];
                pc_signs.push_back("<=");
                rowCtr++;

                // p_vars = pc_vars;
                // p_cons = pc_cons;
            }

            else if(signs[i].compare("=") == 0){
                vector<int> newRow;
                for(int j = 0; j < pc_vars; j++){
                    newRow.push_back(-1 * pc_consr[rowCtr][j]);
                }

                pc_consr.insert(pc_consr.begin() + rowCtr + 1, newRow); //add
                pc_RHS.insert(pc_RHS.begin() + rowCtr + 1, -1 * pc_RHS[rowCtr]);

                pc_cons++;

                pc_signs.push_back("<=");
                pc_signs.push_back("<=");

                // p_vars = pc_vars;
                // p_cons = pc_cons;

                rowCtr++;
                rowCtr++;

                if(rowCtr > pc_cons)
                    rowCtr--;
            }

            else{
                cout<<"Invalid inequality!"<<endl;
                exit(0);
            }
        }
    }

    else if(scope.compare("min") == 0){
        for(int i = 0; i < p_cons; i++){

            if(signs[i].compare(">=") == 0){
                pc_signs.push_back(">=");
                rowCtr++;
                // p_vars = pc_vars;
                // p_cons = pc_cons;
            }

            else if(signs[i].compare("<=") == 0){
                for(int j = 0; j < pc_vars; j++){
                    pc_consr[rowCtr][j] = -1 * pc_consr[rowCtr][j];
                }

                pc_RHS[rowCtr] = -1 * pc_RHS[rowCtr];
                pc_signs.push_back(">=");

                rowCtr++;

                // p_vars = pc_vars;
                // p_cons = pc_cons;
            }

            else if(signs[i].compare("=") == 0){
                vector<int> newRow;

                for(int j = 0; j < pc_vars; j++){
                    newRow.push_back(-1 * pc_consr[rowCtr][j]);
                }

                pc_consr.insert(pc_consr.begin() + rowCtr + 1, newRow);
                pc_RHS.insert(pc_RHS.begin() + i + 1, -1 * pc_RHS[rowCtr]);

                pc_cons++;

                pc_signs.push_back(">=");
                pc_signs.push_back(">=");

                // p_vars = pc_vars;
                // p_cons = pc_cons;

                rowCtr++;
                rowCtr++;

                if(rowCtr > pc_cons)
                    rowCtr--;
            }

            else{
                cout<<"Invalid inequality!"<<endl;
                exit(0);
            }
        }
    }

    else{
        cout<<"Invalid Scope Input!"<<endl;
        exit(0);
    }
}

void dual_canon(int &pc_vars,
                int &pc_cons,
                string &scope,
                vector<int> &pc_obj,
                vector<int> &pc_RHS,
                vector<string> &pc_signs,
                vector<vector<int>> &pc_consr,
                vector<string> &pc_domain,
                string &d_scope,
                int &dc_vars,
                int &dc_cons,
                vector<int> &dc_obj,
                vector<int> &dc_RHS,
                vector<string> &dc_signs,
                vector<vector<int>> &dc_consr,
                vector<string> &dc_domain)
{
    // vector<vector<int>> dc_consr;
    // vector<int> dc_obj;
    // vector<int> dc_RHS;
    // vector<string> dc_signs;

    dc_cons = pc_vars; //dual constraints = primal variables = primal columns
    dc_vars = pc_cons; //dual variables = primal constraints = primal rows
    // string d_scope;

    //changing the scope of the dual
    if(scope.compare("min") == 0)
        d_scope = "max";
    else if(scope.compare("max") == 0)
        d_scope = "min";
    else{
        cout<<"Invalid scope!";
        exit(0);
    }

    //creating the canonical dual's objective function
    for(int i = 0; i < dc_vars; i++){
        dc_obj.push_back(pc_RHS[i]);
    }

    //creating the canonical dual's RHS
    for(int i = 0; i < dc_cons; i++){
        dc_RHS.push_back(pc_obj[i]);
    }

	//transposing the constraint matrix
	int row = 0;
	int col = 0;

	while(row < dc_cons){
		vector<int> newRow;
		col = 0;
		while(col < dc_vars){
			newRow.push_back(pc_consr[col][row]);
			col++;
		}
		dc_consr.push_back(newRow);
		row++;
	}

    //assigning the inequality signs vector
    if(d_scope.compare("min") == 0){
        for(int i = 0; i < dc_cons; i++){
            dc_signs.push_back(">=");
        }
    }

    else if(d_scope.compare("max") == 0){
        for(int i = 0; i < dc_cons; i++){
            dc_signs.push_back("<=");
        }
    }

    else{
        cout<<"Invalid scope input!";
        exit(0);
    }

    //assigning domain to all variables
    for(int i = 0; i < dc_vars; i++){
        dc_domain.push_back("P");
    }
}

int truncRows(vector<int> &v1, vector<int> &v2){ //truncating function to reduce number of rows
    int n = v1.size();
    int ctr = 0;
    for(int i = 0; i < n; i++){
        if(v2[i] == -1 * v1[i])
            ctr++;
    }
    if(ctr == n)
        return 1;
    else
        return 0;
}

int truncCols(int &x, int &times, vector<vector<int>> &matrix){ //truncating function to reduce number of columns
    int ctr = 0;
    for(int i = 0; i < times; i++){
        if(matrix[i][x] == -1 * matrix[i][x + 1])
            ctr++;
    }
    if(ctr == times){
        return x + 1;
    }else{
        return -1;
    }
}

void general_Dual(int &dc_vars,
                int &dc_cons,
                string &d_scope,
                vector<int> &dc_obj,
                vector<int> &dc_RHS,
                vector<string> &dc_signs,
                vector<vector<int>> &dc_consr,
                vector<string> &dc_domain,
                vector<vector<int>> &dg_consr,
                vector<int> &dg_obj,
                vector<int> &dg_RHS,
                vector<string> &dg_domain,
                vector<string> &dg_signs,
                int &dg_vars,
                int &dg_cons)
{
    // int d_vars = p_cons;
    // int d_cons = p_vars;

    dg_vars = dc_vars;
    dg_cons = dc_cons;

    dg_consr = dc_consr;
    dg_obj = dc_obj;
    dg_RHS = dc_RHS;
    dg_domain = dc_domain;
    dg_signs = dc_signs;

    vector<int> delColVec;
    // vector<string> dg_signs = dc_signs;
    // vector<vector<int>> dg_consr = dc_consr;

    for(int i = 0; i < dc_vars - 1; i++){
        if(dc_obj[i] = -1 * dc_obj[i + 1]){
            int delCol = truncCols(i, dc_cons, dc_consr);
            if(delCol != -1)
                delColVec.push_back(delCol);
        }
    }

    int delColVecLen = delColVec.size();

    //truncating columns
    for(int i = delColVecLen - 1; i >= 0; i--){
        dg_obj.erase(dg_obj.begin() + delColVec[i]);
        for(int r = 0; r < dc_cons; r++){
            dg_consr[r].erase(dg_consr[r].begin() + delColVec[i]);
        }
        dg_vars--;
        for(int j = i; j < delColVecLen; j++){
            delColVec[j] = delColVec[j] - 1; //storing the indices of the real variables
        }
    }


    //truncating rows
    for(int i = dc_cons - 2; i >= 0; i--){
        int tr = truncRows(dg_consr[i], dg_consr[i + 1]);
        if(tr == 1){
            dg_consr.erase(dg_consr.begin() + i + 1);
            dg_RHS.erase(dg_RHS.begin() + i + 1);
            dg_signs.erase(dg_signs.begin() + i + 1);
            dg_signs.erase(dg_signs.begin() + i);
            dg_signs.insert(dg_signs.begin() + i, "=");
            dg_cons--;
        }
    }

    for(int i = 0; i < delColVecLen; i++){
        dg_domain[delColVec[i]] = "R";
    }
}
