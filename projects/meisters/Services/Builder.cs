using Autofac;
using Meisters.Models;
using Meisters.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Services
{
    public class Builder
    {
        public Builder()
        {
            var containerBuilder = new ContainerBuilder();

            // ViewModels
            containerBuilder.RegisterType<FloorViewModel>().AsSelf().SingleInstance();
            containerBuilder.RegisterType<ReservationViewModel>().AsSelf().SingleInstance();

            // Models
            containerBuilder.RegisterType<TablesModel>().AsSelf().SingleInstance();
            containerBuilder.RegisterType<EmployeesModel>().AsSelf().SingleInstance();

            Container = containerBuilder.Build();
        }

        public IContainer Container { get; }

        internal void Init()
        {
            // Models
            Container.Resolve<TablesModel>();
            Container.Resolve<EmployeesModel>();
        }

        // ViewModels
        public FloorViewModel Floor => Container.Resolve<FloorViewModel>();
        public ReservationViewModel Reservation => Container.Resolve<ReservationViewModel>();
    }
}
