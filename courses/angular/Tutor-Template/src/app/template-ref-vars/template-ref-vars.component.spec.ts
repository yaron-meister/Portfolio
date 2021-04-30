import { ComponentFixture, TestBed } from '@angular/core/testing';

import { TemplateRefVarsComponent } from './template-ref-vars.component';

describe('TemplateRefVarsComponent', () => {
  let component: TemplateRefVarsComponent;
  let fixture: ComponentFixture<TemplateRefVarsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ TemplateRefVarsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(TemplateRefVarsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
