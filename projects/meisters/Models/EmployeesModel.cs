using Meisters.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public class EmployeesModel
    {
        public EmployeesModel()
        {
            EmployeesData.ActiveEmployees.Add(EmployeesData.GeneralEmployee);
            SelectEmployee(EmployeesData.GeneralEmployee);
        }

        public EmployeesData EmployeesData { get; } = new EmployeesData();

        public void SelectActiveEmployee(Employee employee)
        {
            if (employee?.Uid != EmployeesData.SelectedEmployee?.Uid)
            {
                if (EmployeesData.SelectedEmployee != null)
                {
                    EmployeesData.SelectedEmployee.IsSelected = false;
                }
                SelectEmployee(employee);
            }
        }

        public void ActivateSelectedEmployee(Employee employee)
        {
            if (employee != null && employee != EmployeesData.GeneralEmployee)
            {
                EmployeesData.ActiveEmployees.Add(employee);
                EmployeesData.InactiveEmployees.Remove(employee);
            }
        }

        public void DiscardEmployee(Employee employee)
        {
            if (employee != null && employee != EmployeesData.GeneralEmployee)
            {
                EmployeesData.InactiveEmployees.Add(employee);
                EmployeesData.ActiveEmployees.Remove(employee);
                EmployeesData.SelectedEmployee = EmployeesData.GeneralEmployee;
            }
        }

        private void SelectEmployee(Employee employee)
        {
            EmployeesData.SelectedEmployee = employee;
            EmployeesData.SelectedEmployee.IsSelected = true;
        }
    }
}
