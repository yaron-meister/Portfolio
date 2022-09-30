using GalaSoft.MvvmLight.Command;
using Meisters.Data;
using Meisters.Models;
using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Threading;

namespace Meisters.ViewModels
{
    public class FloorViewModel : ViewModelBase
    {
        //void dt_Tick(object sender, EventArgs e)
        //{
        //    if (stopWatch.IsRunning)
        //    {
        //        TimeSpan ts = stopWatch.Elapsed;
        //        currentTime = String.Format("{0:00}:{1:00}:{2:00}",
        //        ts.Minutes, ts.Seconds, ts.Milliseconds / 10);
        //        clocktxt.Text = currentTime;
        //    }
        //}

        //private void startbtn_Click(object sender, RoutedEventArgs e)
        //{
        //    stopWatch.Start();
        //    dispatcherTimer.Start();
        //}

        //private void stopbtn_Click(object sender, RoutedEventArgs e)
        //{
        //    if (stopWatch.IsRunning)
        //    {
        //        stopWatch.Stop();
        //    }
        //    elapsedtimeitem.Items.Add(currentTime);
        //}

        //private void resetbtn_Click(object sender, RoutedEventArgs e)
        //{
        //    stopWatch.Reset();
        //    clocktxt.Text = "00:00:00";
        //}

        private readonly int ONE_MINUTE = 1;

        private readonly TablesModel _tablesModel;
        private readonly EmployeesModel _employeesModel;

        private string _searchText = string.Empty;
        private bool _isActivatingEmp = false;
        private DispatcherTimer _dispatcherTimer = new DispatcherTimer();
        private IEnumerable<Employee> _filteredInactiveEmployees = new ObservableCollection<Employee>();

        public FloorViewModel(TablesModel tablesModel, EmployeesModel employeesModel)
        {
            _tablesModel = tablesModel;
            _employeesModel = employeesModel;

            // This DispatcherTimer is for updating the Tables stopwatches in the UI
            _dispatcherTimer.Tick += (object sender, EventArgs e) =>
            {
                OnPropertyChanged(nameof(TablesData));
            };
            _dispatcherTimer.Interval = new TimeSpan(0, ONE_MINUTE, 0);
            _dispatcherTimer.Start();
        }


        public TablesData TablesData => _tablesModel.TablesData;
        public EmployeesData EmployeesData => _employeesModel.EmployeesData;

        public string SearchText
        {
            get => _searchText;
            set
            {
                _searchText = value;
                OnPropertyChanged();
                FilterInactiveEmployees();
            }
        }

        public bool IsActivatingEmp
        {
            get => _isActivatingEmp;
            set
            {
                _isActivatingEmp = value;
                OnPropertyChanged();
            }
        }

        public IEnumerable<Employee> FilteredInactiveEmployees
        {
            get => _filteredInactiveEmployees;
            set
            {
                _filteredInactiveEmployees = value;
                OnPropertyChanged();
            }
        }


        #region Commands

        public ICommand SelectActiveEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            _employeesModel.SelectActiveEmployee(employee);
        });

        public ICommand ActivateEmployeeCommand => new RelayCommand(() =>
        {
            // TODO::YARON - Disable "Activate" button if Inactive  is empty
            FilteredInactiveEmployees = EmployeesData.InactiveEmployees;
            if (FilteredInactiveEmployees.Count() != 0)
            {
                _employeesModel.SelectActiveEmployee(FilteredInactiveEmployees.First());
                IsActivatingEmp = true;
            }
        });

        public ICommand DiscardEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            _employeesModel.DiscardEmployee(employee);
        });

        public ICommand ActivateSelectedEmpCommand => new RelayCommand<Employee>((employee) =>
        {
            _employeesModel.ActivateSelectedEmployee(employee);
            CloseEmpActivision();
        });

        public ICommand CancelEmpActivisionCommand => new RelayCommand(() =>
        {
            CloseEmpActivision();
        });

        public ICommand StepIntoTableCommand => new RelayCommand<string>((idStr) =>
        {
            if (int.TryParse(idStr, out int id))
            {
                _tablesModel.StepIntoTable(id);
            }
        });

        #endregion Commands


        private void FilterInactiveEmployees()
        {
            if (!string.IsNullOrEmpty(SearchText))
            {
                FilteredInactiveEmployees = EmployeesData.InactiveEmployees.Where(employee =>
                                                employee.Name.ToLower().Contains(SearchText.ToLower()));
            }
            else
            {
                FilteredInactiveEmployees = EmployeesData.InactiveEmployees;
            }
        }

        private void CloseEmpActivision()
        {
            _employeesModel.SelectActiveEmployee(EmployeesData.GeneralEmployee);
            IsActivatingEmp = false;
        }
    }
}
